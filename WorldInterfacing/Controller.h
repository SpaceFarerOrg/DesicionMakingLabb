#pragma once
#include <SFML\System\Vector2.hpp>
#include "MouseInputHandler.h"
#include <vector>

class CSteeringBehaviour;
class CPollingStation;
class CButton;

class CController
{
public:
	virtual void Update(class CActor& aActor ,float aDeltaTime);

	void SetActorData(float aMaxSpeed);

	void SetSteeringBehaviour(CSteeringBehaviour* aSB);
protected:
	float mySpeed;
	float myMaxSpeed;
	CSteeringBehaviour* myBehaviour = nullptr;
};

