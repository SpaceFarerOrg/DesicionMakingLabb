#pragma once
#include <SFML\Graphics\Texture.hpp>
#include "Actor.h"
#include "Button.h"
#include "PollingStation.h"
#include <vector>
#include "AIEventManager.h"
#include "SheepManager.h"
#include "HealthPickup.h"

enum class ETextureIndexes
{
	Button,
	Player,
	Poller,
	Pusher,
	Room,
	Alarm,
	Fleer,
	Arriver,
	HealthPickup,
	Count,
};


namespace sf
{
	class RenderWindow;
}

class CGame
{
public:
	CGame(bool& aShouldRun);
	CGame() = delete;
	~CGame();
	void Init();
	void Update(float aDT);
	void Render();
private:
	void ReInit();

	void RunAlarm();

	CAIEventManager myAIEventManager;
	CPollingStation myPollingStation;

	static const int ActorCount = 2;
	std::vector<CActor> myActors;
	std::vector<CHealthPickup> myHealthPickups;

	float myAlarmTimer;

	sf::Sprite myAlarmSprite;
	sf::Sprite myFloorSprite;
	sf::Sprite myHealthPackSprite;
	
	bool IsCloseToHealthPack(const sf::Vector2f& aPos, float aMinDist);
	void LoadTextures();
	sf::Vector2f FindSuitableHealthPackPos();
	sf::Texture myTextures[(unsigned)ETextureIndexes::Count];

	CSheepManager mySheepManager;

	sf::RenderWindow* myWindow;
	bool& myShouldRun;

	sf::Vector2f& GetMouseClickPosition();
	sf::Vector2f myLatestClickPosition;
	const sf::Vector2f& GetArriverPos();
	sf::Vector2f myLatestArriverPos;
};