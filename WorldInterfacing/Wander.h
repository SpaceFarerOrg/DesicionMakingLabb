#pragma once
#include "SteeringBehaviour.h"
#include "Math.h"

class CWander : public CSteeringBehaviour
{
public:
	CWander() : CSteeringBehaviour(nullptr) { myTurnAngle = 6.28f * Math::Random(); };
	const sf::Vector2f& Update(CSteeringBehaviour::SSteeringData aData) override;
private:
	float myTurnAngle;
};