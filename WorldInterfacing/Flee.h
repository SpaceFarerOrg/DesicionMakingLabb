#pragma once
#include "SteeringBehaviour.h"
#include "PollingStation.h"

class CFlee : public CSteeringBehaviour
{
public:
	CFlee(CPollingStation* aPollingStation) : CSteeringBehaviour(aPollingStation) { myDangerZone = 350.f; }

	const sf::Vector2f& Update(CSteeringBehaviour::SSteeringData aData) override;
	
private:
	float myDangerZone;
};

