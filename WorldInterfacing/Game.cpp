#include "Game.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "Controller.h"
#include "DecisionTreeController.h"
#include "StateMachineController.h"
#include "FuzzyLogicController.h"
#include "MouseInputHandler.h"
#include "Arrive.h"
#include "Flee.h"
#include "Wander.h"
#include "ProjectileManager.h"

CGame::CGame(bool & aShouldRun)
	:myShouldRun(aShouldRun)
{
	myAlarmTimer = 0.f;
}

CGame::~CGame()
{
	delete myWindow;
}

void CGame::Init()
{
	myWindow = new sf::RenderWindow();
	
	CMouseInputHandler::SetWindowToGetRelativePositionTo(myWindow);

	sf::VideoMode vm;
	vm.width = 1600;
	vm.height = 900;

	myWindow->create(vm, "World Interfacing", sf::Style::Close | sf::Style::Titlebar);

	LoadTextures();

	myHealthPackSprite.setTexture(myTextures[(unsigned)ETextureIndexes::HealthPickup]);
	myHealthPackSprite.setOrigin(32, 32);

	myPollingStation.RegisterFunction(CPollingStation::EPollableValue::latestClickedPos, [&]()->const sf::Vector2f&{ return GetMouseClickPosition(); });
	myPollingStation.RegisterFunction(CPollingStation::EPollableValue::arriverPos, [&]()->const sf::Vector2f&{ return GetArriverPos(); });

	myActors.reserve(ActorCount);
	myActors.push_back(CActor());
	myActors.back().Create(myTextures[(unsigned)ETextureIndexes::Player], 150.f, 0);
	myActors.back().AttatchController(new CStateMachineController());
	myActors.back().GetController()->SetSteeringBehaviour(new CWander()); 

	myActors.push_back(CActor());
	myActors.back().Create(myTextures[(unsigned)ETextureIndexes::Pusher], 150.f, 1);
	myActors.back().AttatchController(new CDecisionTreeController());
	myActors.back().GetController()->SetSteeringBehaviour(new CWander());

	myActors.push_back(CActor());
	myActors.back().Create(myTextures[(unsigned)ETextureIndexes::Arriver], 150.f, 2);
	myActors.back().AttatchController(new CFuzzyLogicController());
	myActors.back().GetController()->SetSteeringBehaviour(new CWander());

	myPowerUP.first.setTexture(myTextures[(unsigned)ETextureIndexes::PowerUP]);
	myPowerUP.first.setPosition(vm.width * 0.5f, vm.height * 0.5f);
	myPowerUP.first.setOrigin(myPowerUP.first.getGlobalBounds().width * 0.5f, myPowerUP.first.getGlobalBounds().height * 0.5f);
	myPowerUP.second = false;
	myPowerUPTimer = 0.f;

	myHealthPickups.reserve(4);
	for (unsigned i = 0; i < 4; ++i)
	{
		myHealthPickups.push_back(CHealthPickup());

		sf::Vector2f pos = FindSuitableHealthPackPos();

		myHealthPickups[i].SetPosition(pos);
	}
	//myActors[0].Create(myTextures[(unsigned)ETextureIndexes::Arriver], 300.f, 0);
	//myActors[0].GetController()->AttachSteeringBehaviour(new CArrive(&myPollingStation));
	//myLatestClickPosition = myActors[0].GetPosition();

	CActor::SetActorList(&myActors);
	CActor::SetHealthPickupList(&myHealthPickups);
	CActor::SetPowerUp(&myPowerUP);

	myFloorSprite.setTexture(myTextures[(unsigned)ETextureIndexes::Room]);
	myAlarmSprite.setTexture(myTextures[(unsigned)ETextureIndexes::Alarm]);

	myAIEventManager.SubscribeToEvent(CAIEventManager::EAIEvents::ButtonPressed, [&](const sf::Vector2f& aPos)->void { RunAlarm(); });

}

void CGame::Update(float aDT)
{
	if (myPowerUPTimer < 0.f)
	{
		myPowerUPTimer += aDT;
	}
	if (myPowerUPTimer >= 0.f)
	{
		myPowerUP.second = false;
	}

	myAlarmSprite.setColor({ 255,255,255,0 });
	myAlarmTimer += 2.5 * aDT;

	myPollingStation.BeginFrame();
	myAIEventManager.DispatchEvents();

	sf::Event e;
	myWindow->pollEvent(e);

	if (e.type == sf::Event::Closed)
		myShouldRun = false;

	for (CHealthPickup& hp : myHealthPickups)
	{
		if (hp.GetIsActive() == false)
		{
			hp.SetPosition(FindSuitableHealthPackPos());
			hp.Activate();
		}
	}

	for (unsigned i = 0; i < ActorCount; ++i)
	{
		myActors[i].Update(aDT);
		if (myActors[i].IsActive())
		{
			if (CProjectileManager::GetInstance().CheckCollisionAgainst(myActors[i].GetPosition(), myActors[i].GetSprite().getGlobalBounds().width / 2, myActors[i].GetID()))
			{
				myActors[i].Damage(20);
			}
		}
	}
	if (myPowerUP.second && myPowerUPTimer >= 0.f)
	{
		myPowerUPTimer = -5.f;
	}

	CProjectileManager::GetInstance().Update(aDT);
}

void CGame::Render()
{
	myWindow->clear({ 50,150,255,255 });

	myWindow->draw(myFloorSprite);

	for (unsigned i = 0; i < ActorCount; ++i)
	{
		if (myActors[i].IsActive())
		{
			myActors[i].Render(myWindow);
		}
	}

	for (unsigned i = 0; i < myHealthPickups.size(); ++i)
	{
		myHealthPackSprite.setPosition(myHealthPickups[i].GetPosition());
		myWindow->draw(myHealthPackSprite);
	}

	if (myPowerUPTimer >= 0.f)
	{
		myWindow->draw(myPowerUP.first);
	}

	CProjectileManager::GetInstance().Render(myWindow);

	myWindow->draw(myAlarmSprite);

	myWindow->display();
}

void CGame::ReInit()
{
}


void CGame::RunAlarm()
{
	unsigned i = (unsigned)(255 * (fabs((sinf(myAlarmTimer)))));
	sf::Uint8 iu8 = (sf::Uint8)i;

	myAlarmSprite.setColor({ 255,255,255, iu8});
}

bool CGame::IsCloseToHealthPack(const sf::Vector2f & aPos, float aMinDist)
{
	for (CHealthPickup& pickup : myHealthPickups)
	{ 
		if (Math::Length(aPos - pickup.GetPosition()) < aMinDist)
			return true; 
	} 
	return false;
}

void CGame::LoadTextures()
{
	myTextures[(unsigned)ETextureIndexes::Room].loadFromFile("textures/Room.png");
	myTextures[(unsigned)ETextureIndexes::Player].loadFromFile("textures/Player.png");
	myTextures[(unsigned)ETextureIndexes::Poller].loadFromFile("textures/Poller.png");
	myTextures[(unsigned)ETextureIndexes::Pusher].loadFromFile("textures/Pusher.png");
	myTextures[(unsigned)ETextureIndexes::Button].loadFromFile("textures/Button.png");
	myTextures[(unsigned)ETextureIndexes::Alarm].loadFromFile("textures/Alarm.png");
	myTextures[(unsigned)ETextureIndexes::Fleer].loadFromFile("textures/Fleer.png");
	myTextures[(unsigned)ETextureIndexes::Arriver].loadFromFile("textures/Arriver.png");
	myTextures[(unsigned)ETextureIndexes::HealthPickup].loadFromFile("textures/HealthPickup.png");
	myTextures[(unsigned)ETextureIndexes::PowerUP].loadFromFile("textures/PowerUP.png");
}

sf::Vector2f CGame::FindSuitableHealthPackPos()
{
	sf::Vector2f rv;

	for (CHealthPickup& hp : myHealthPickups)
	{
		do 
		{
			rv.x = 25 + rand() % (1575 - 25);
			rv.y = 170 + rand() % (875 - 170);
		} while (IsCloseToHealthPack(rv, 450.f));
	}

	return rv;
}

sf::Vector2f & CGame::GetMouseClickPosition()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		myLatestClickPosition = { (float)sf::Mouse::getPosition(*myWindow).x, (float)sf::Mouse::getPosition(*myWindow).y };
	}

	return myLatestClickPosition;
}

const sf::Vector2f & CGame::GetArriverPos()
{
	return myActors[0].GetPosition();
}
