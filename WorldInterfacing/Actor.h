#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Vector2.hpp>
#include "Weapon.h"
#include <vector>
#include "HealthPickup.h"
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class CController;

namespace sf
{
	class RenderWindow;
}

class CActor
{
public:
	static void SetActorList(std::vector<CActor>* aActorList);
	static void SetHealthPickupList(std::vector<CHealthPickup>* aHealthPickupList);

	void Create(sf::Texture& aTexture, float aSpeed, int aID);
	void ReInit();

	void AttatchController(CController* aController);
	CController* GetController();

	const sf::Vector2f& GetPosition();
	const sf::Vector2f& GetDirection();
	float GetSpeed();
	const sf::Sprite& const GetSprite();
	int GetID();
	const bool IsActive();
	void Damage(int aDamage);

	void SetDirection(const sf::Vector2f& aDirection);
	void SetPosition(const sf::Vector2f& aPosition);
	void SetIsActive(bool aIsActive);

	void Move(const sf::Vector2f& aMovement);

	void Update(float aDT);
	void Render(sf::RenderWindow* aWindow);

	//State Machine stuff here  \/
	int GetHealth();
	bool CanSeeEnemy();
	CActor* GetClosestEnemy();
	CWeapon* GetWeapon();
	bool FindClosestHealthPickup();
	bool PickUpHealth(int aValue);
	const sf::Vector2f& GetTarget();
	void SetTarget(const sf::Vector2f& aTarget);

private:
	float mySpeed;
	sf::Sprite mySprite;
	sf::Vector2f myPosition;
	sf::Vector2f myDirection;
	CController* myController;
	CWeapon myWeapon;
	bool myIsActive;
	float myRespawnTimer;
	int myID;
	int myHealth;
	CActor* myClosestActor;
	sf::Vector2f myTarget;

	static std::vector<CActor>* ourFellowActors;
	static std::vector<CHealthPickup>* ourAvailableHealthPickups;

	static sf::Font ourFont;
	sf::Text myText;
};