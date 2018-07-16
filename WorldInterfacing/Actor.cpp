#include "Actor.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "Controller.h"
#include "Math.h"
#include "HealthPickup.h"

std::vector<CActor>* CActor::ourFellowActors;
std::vector<CHealthPickup>* CActor::ourAvailableHealthPickups;

sf::Font CActor::ourFont;

void CActor::SetActorList(std::vector<CActor>* aActorList)
{
	ourFellowActors = aActorList;
}

void CActor::SetHealthPickupList(std::vector<CHealthPickup>* aHealthPickupList)
{
	ourAvailableHealthPickups = aHealthPickupList;
}

void CActor::Create(sf::Texture & aTexture, float aSpeed, int aID)
{
	if (aID == 0)
	{
		ourFont.loadFromFile("fonts/arial.ttf");
	}
	myText.setFont(ourFont);
	myText.setFillColor(sf::Color::Red);

	myID = aID;
	mySprite.setTexture(aTexture);

	mySpeed = aSpeed;
	ReInit();

	mySprite.setOrigin({ mySprite.getGlobalBounds().width / 2.f, mySprite.getGlobalBounds().height / 2.f });

	myWeapon.SetActor(this);
	myWeapon.SetDelay(0.75f);
	myWeapon.SetProjectileSpeed(1500.f);
	myRespawnTimer = 0.f;
	myIsActive = true;
	myHealth = 100;
}

void CActor::ReInit()
{
	myPosition.x = (float)(rand() % 1400);
	myPosition.y = (float)(rand() % 700) + 200;
}

void CActor::AttatchController(CController * aController)
{
	myController = aController;
	myController->SetActorData(mySpeed);
}

CController * CActor::GetController()
{
	return myController;
}

const sf::Vector2f & CActor::GetPosition()
{
	return myPosition;
}

const sf::Vector2f & CActor::GetDirection()
{
	return myDirection;
}

void CActor::SetDirection(const sf::Vector2f & aDirection)
{
	myDirection = aDirection;
}

void CActor::SetPosition(const sf::Vector2f & aPosition)
{
	myPosition = aPosition;
}

void CActor::SetIsActive(bool aIsActive)
{
	myIsActive = aIsActive;
}

float CActor::GetSpeed()
{
	return mySpeed;
}

int CActor::GetHealth()
{
	return myHealth;
}

bool CActor::CanSeeEnemy()
{
	float shortestDistance = 10000.f;
	CActor* closestActor = nullptr;

	for (CActor& other : *ourFellowActors)
	{
		if (other.GetID() == myID || other.IsActive() == false)
			continue;
	
		float distance = Math::Length(other.GetPosition() - myPosition);
	
		if (distance < std::min(shortestDistance, 450.f))
		{
			shortestDistance = distance;
			closestActor = &other;
			myClosestActor = closestActor;
		}
	}
	
	if (closestActor)
		return true;

	return false;
}

CActor * CActor::GetClosestEnemy()
{
	return myClosestActor;
}

CWeapon * CActor::GetWeapon()
{
	return &myWeapon;
}

bool CActor::FindClosestHealthPickup()
{
	bool foundHealthPack = false;
	sf::Vector2f closest;
	float distance = 9999999;
	for (CHealthPickup& hp : *ourAvailableHealthPickups)
	{
		float currentDist = Math::Length(hp.GetPosition() - myPosition);
		if (currentDist < distance)
		{
			distance = currentDist;
			closest = hp.GetPosition();
			foundHealthPack = true;
		}
	}
	if (foundHealthPack)
	{
		myTarget = closest;
	}

	return foundHealthPack;
}

bool CActor::PickUpHealth(int aValue)
{
	if (myHealth < 100)
	{
		myHealth = Math::Clamp(myHealth + aValue, myHealth, 100);
		return true;
	}
	return false;
}

const sf::Vector2f& CActor::GetTarget()
{
	return myTarget;
}

void CActor::SetTarget(const sf::Vector2f & aTarget)
{
	myTarget = aTarget;
}

const sf::Sprite & const CActor::GetSprite()
{
	return mySprite;
}

int CActor::GetID()
{
	return myID;
}

const bool CActor::IsActive()
{
	return myIsActive;
}

void CActor::Damage(int aDamage)
{
	myHealth -= aDamage;

	if (myHealth <= 0)
		SetIsActive(false);
}

void CActor::Move(const sf::Vector2f & aMovement)
{
	myPosition += aMovement;
}

void CActor::Update(float aDT)
{
	myController->Update(*this, aDT);

	if (myIsActive == false)
	{
		myRespawnTimer += aDT;

		if (myRespawnTimer > 3.0f)
		{
			myIsActive = true;
			myHealth = 100;
			myRespawnTimer = 0.f;
		}
	}
	else
	{
		myWeapon.Update(aDT);

		for (CHealthPickup& hp : *ourAvailableHealthPickups)
		{
			if (Math::Length2(hp.GetPosition() - myPosition) < 64.f * 64.f)
			{
				if (PickUpHealth(100))
					hp.PickUp();
			}
		}
	}

	myPosition.y = Math::Clamp(myPosition.y, 170.f, 875.f);
	myPosition.x = Math::Clamp(myPosition.x, 25.f, 1575.f);
}

void CActor::Render(sf::RenderWindow * aWindow)
{
	sf::Vector2f textOffset = {0,20};
	myText.setString(sf::String(std::to_string(myHealth)));

	mySprite.setPosition(myPosition);
	myText.setPosition(myPosition + textOffset);
	aWindow->draw(mySprite);
	aWindow->draw(myText);
}
