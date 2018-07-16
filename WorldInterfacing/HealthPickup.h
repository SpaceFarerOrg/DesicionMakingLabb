#pragma once
#include "SFML/System/Vector2.hpp"

class CHealthPickup
{
public:
	CHealthPickup();
	~CHealthPickup();

	void SetPosition(const sf::Vector2f& aPosition);
	sf::Vector2f GetPosition();

	void PickUp();
	bool GetIsActive();
	void Activate();

private:

	sf::Vector2f myPosition;
	bool myIsActive;
};

