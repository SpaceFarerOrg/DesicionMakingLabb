#include "ProjectileManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Math.h"

CProjectileManager& CProjectileManager::GetInstance()
{
	static CProjectileManager me;
	return me;
}

void CProjectileManager::Update(float aDT)
{
	for (int i = 0; i < myProjectiles.size(); ++i)
	{
		myProjectiles[i].myPosition += myProjectiles[i].myDirection * myProjectiles[i].mySpeed * aDT;
	}
}

void CProjectileManager::Render(sf::RenderWindow * aRenderWindow)
{
	for (SProjetile& projectile : myProjectiles)
	{
		myProjectileSprite.setPosition(projectile.myPosition);
		aRenderWindow->draw(myProjectileSprite);
	}
}

void CProjectileManager::SpawnProjectile(const SProjetile & aProjectile)
{
	myProjectiles[myIndex++] = aProjectile;
	if (myIndex >= myProjectiles.size())
	{
		myIndex = 0;
	}
}

bool CProjectileManager::CheckCollisionAgainst(const sf::Vector2f & aPos, float aRadius, int aID)
{
	for (int i = 0; i < myProjectiles.size(); ++i)
	{
		if (aID == myProjectiles[i].myIDToIgnore)
			continue;

		if (Math::Length(myProjectiles[i].myPosition - aPos) < aRadius)
		{
			myProjectiles[i] = SProjetile();
			myProjectiles[i].myPosition = {10000.f, 10000.f};
			return true;
		}
	}
	return false;
}

CProjectileManager::CProjectileManager()
{
	myIndex = 0;
	myProjectiles.reserve(128);
	for (int i = 0; i < 128; ++i)
	{
		myProjectiles.push_back(SProjetile());
	}

	myProjectileTexture.loadFromFile("textures/Button.png");
	myProjectileSprite.setTexture(myProjectileTexture);
	myProjectileSprite.setOrigin(myProjectileSprite.getGlobalBounds().width / 2, myProjectileSprite.getGlobalBounds().height / 2);
}


CProjectileManager::~CProjectileManager()
{
}
