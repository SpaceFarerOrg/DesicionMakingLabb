#pragma once
#include "SFML/System/Vector2.hpp"

class CWeapon
{
public:
	CWeapon();
	~CWeapon();

	void SetProjectileSpeed(float aSpeed);
	void SetDelay(float aDelay);
	void SetActor(class CActor* aActor);

	void Update(float aDT);
	void Shoot();
	void AimAt(const sf::Vector2f& aPosition);

private:
	CActor* myActor;
	sf::Vector2f myDirection;
	float myProjectileSpeed;
	float myDelay;
	float myTimer;
	bool myCanShoot;
};

