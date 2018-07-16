#include "Controller.h"
#include "MouseInputHandler.h"
#include "Math.h"
#include "SteeringBehaviour.h"
#include "Actor.h"

void CController::Update(CActor& aActor,float aDT)
{
	if (myBehaviour == nullptr)
		return;
	
	sf::Vector2f currentPos = aActor.GetPosition();
	sf::Vector2f currentDir = aActor.GetDirection();

	sf::Vector2f newDirection = myBehaviour->Update({ currentPos, currentDir, mySpeed, myMaxSpeed, aActor });

	sf::Vector2f newPosition = currentPos + newDirection * mySpeed * aDT;

	sf::Vector2f positionDelta = newPosition - currentPos;

	aActor.Move(positionDelta);
	Math::Normalize(positionDelta);
	aActor.SetDirection(positionDelta);
}

void CController::SetActorData(float aMaxSpeed)
{
	myMaxSpeed = aMaxSpeed;
	mySpeed = aMaxSpeed;
}

void CController::SetSteeringBehaviour(CSteeringBehaviour * aSB)
{
	if (myBehaviour != nullptr)
	{
		delete myBehaviour;
		myBehaviour = nullptr;
	}

	myBehaviour = aSB;
}


