#include "Flee.h"
#include "Math.h"
#include <vector>
#include "Actor.h"

const sf::Vector2f & CFlee::Update(CSteeringBehaviour::SSteeringData aData)
{
	sf::Vector2f fleeTarget = aData.actor.GetTarget(); //myPollingStation->PollValue(CPollingStation::EPollableValue::arriverPos);

	sf::Vector2f direction = aData.position - fleeTarget;

	aData.currentSpeed = 0;

	float distance = Math::Length(direction);
	if (distance < myDangerZone)
	{
		aData.currentSpeed = aData.maxSpeed * (1.f - distance / myDangerZone);
	}
	

	Math::Normalize(direction);

	return direction;
}
