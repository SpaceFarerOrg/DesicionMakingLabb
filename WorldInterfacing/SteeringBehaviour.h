#pragma once
#include <SFML\System\Vector2.hpp>
#include "Actor.h"

class CSteeringBehaviour
{
public:
	struct SSteeringData
	{
		SSteeringData(sf::Vector2f& aPos, sf::Vector2f& aDir, float& aCurrentSpeed, float aMaxSpeed, CActor& aActor)
			: position(aPos)
			, direction(aDir)
			, currentSpeed(aCurrentSpeed)
			, maxSpeed(aMaxSpeed)
			, actor(aActor) {}

		sf::Vector2f& position;
		sf::Vector2f& direction;
		float& currentSpeed;
		float maxSpeed;
		CActor& actor;
	};

	CSteeringBehaviour(class CPollingStation* aPollingStation) { myPollingStation = aPollingStation; };

	virtual const sf::Vector2f& Update(SSteeringData aData) = 0;
	CPollingStation* GetPollingStation();

protected:
	CPollingStation* myPollingStation;
};