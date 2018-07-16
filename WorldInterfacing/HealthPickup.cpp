#include "HealthPickup.h"



CHealthPickup::CHealthPickup()
{
}


CHealthPickup::~CHealthPickup()
{
}

void CHealthPickup::SetPosition(const sf::Vector2f & aPosition)
{
	myPosition = aPosition;
}

sf::Vector2f CHealthPickup::GetPosition()
{
	return myPosition;
}

void CHealthPickup::PickUp()
{
	myIsActive = false;
}

bool CHealthPickup::GetIsActive()
{
	return myIsActive;
}

void CHealthPickup::Activate()
{
	myIsActive = true;
}
