#include "Wander.h"
#include "Math.h"

const sf::Vector2f& CWander::Update(CSteeringBehaviour::SSteeringData aData)
{
	float CIRCLE_CENTER = aData.maxSpeed / 2.f;
	//float turnAngle = 1.57f + 0.25f * cosf(rand());

	sf::Vector2f returnVel;

	sf::Vector2f displacementCircle = aData.direction * aData.currentSpeed;
	Math::Normalize(displacementCircle);
	displacementCircle *= CIRCLE_CENTER;

	sf::Vector2f displacement(0, -1);
	displacement *= aData.maxSpeed / 4.f;

	float len = Math::Length(displacement);
	displacement.x = cosf(myTurnAngle)*len;
	displacement.y = sinf(myTurnAngle)*len;

	float rfloat = Math::Random();
	myTurnAngle += (rfloat * 0.16f) - (0.16f * 0.5f);

	returnVel = displacementCircle + displacement;

	Math::Normalize(returnVel);

	return returnVel;
}

