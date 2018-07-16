#pragma once
#include "SteeringBehaviour.h"
#include "PollingStation.h"

class CArrive : public CSteeringBehaviour
{
public:
	CArrive(CPollingStation* aPollingStation) : CSteeringBehaviour(aPollingStation) { mySlowingRadius = 50.f; }
	const sf::Vector2f& Update(CSteeringBehaviour::SSteeringData aData) override;

private:
	float mySlowingRadius;
};
