#include "Weapon.h"
#include "ProjectileManager.h"
#include "Actor.h"
#include "Math.h"

CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
}

void CWeapon::SetProjectileSpeed(float aSpeed)
{
	myProjectileSpeed = aSpeed;
}

void CWeapon::SetDelay(float aDelay)
{
	myDelay = aDelay;
	myTimer = Math::Random() * myDelay;
}

void CWeapon::SetActor(CActor * aActor)
{
	myActor = aActor;
}

void CWeapon::Update(float aDT)
{
	if (myCanShoot == false)
	{
		myTimer += aDT;
		if (myTimer >= myDelay)
		{
			myCanShoot = true;
			myTimer = 0;
		}
	}
}

void CWeapon::Shoot()
{
	if (myCanShoot)
	{
		CProjectileManager::SProjetile projectile;
		projectile.myDirection = myDirection;
		projectile.mySpeed = myProjectileSpeed + myActor->GetSpeed();
		projectile.myPosition = myActor->GetPosition();
		projectile.myIDToIgnore = myActor->GetID();

		CProjectileManager::GetInstance().SpawnProjectile(projectile);
		myCanShoot = false;
	}
}

void CWeapon::AimAt(const sf::Vector2f & aPosition)
{
	myDirection = aPosition - myActor->GetPosition();
	Math::Normalize(myDirection);
}
