#include "Arrive.h"
#include "Math.h"

const sf::Vector2f & CArrive::Update(CSteeringBehaviour::SSteeringData aData)
{
	sf::Vector2f direction;

	direction = aData.direction;

	sf::Vector2f target = aData.actor.GetTarget();

	direction = target - aData.position;
	float distance = Math::Length(direction);

	if (Math::Length2(direction) > 0)
	{
		Math::Normalize(direction);
	}

	aData.currentSpeed = aData.maxSpeed;

	if (distance < mySlowingRadius)
	{
		aData.currentSpeed *= (distance / mySlowingRadius);
	}

	return direction;
}
