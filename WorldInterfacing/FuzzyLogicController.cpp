#include "FuzzyLogicController.h"
#include "Actor.h"
#include "Math.h"
#include "SteeringBehaviours.h"

CFuzzyLogicController::CFuzzyLogicController()
{
}

CFuzzyLogicController::~CFuzzyLogicController()
{
}

void CFuzzyLogicController::Update(CActor & aActor, float aDT)
{
	if (IsHealthy(aActor) < 0.25f)
	{
		if (aActor.FindClosestHealthPickup())
		{
			myDecision = 0;
			if (myDecision != myPrevDecision)
			{
				SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
			}
		}
	}
	else if (IsThreatened(aActor) > 0.25f)
	{
		if (IsThreatened(aActor) > 0.5f)
		{
			myDecision = 1;
			if (myDecision != myPrevDecision)
			{
				SetSteeringBehaviour(new CFlee(myBehaviour->GetPollingStation()));
			}
		}
		aActor.GetWeapon()->AimAt(aActor.GetClosestEnemy()->GetPosition());
		aActor.GetWeapon()->Shoot();
		if (IsConfident(aActor) >= 0.f)
		{
			aActor.SetTarget(aActor.GetClosestEnemy()->GetPosition());
		}
	}
	else
	{
		myDecision = 3;
		if (myDecision != myPrevDecision)
		{
			SetSteeringBehaviour(new CWander());
		}
	}

	myPrevDecision = myDecision;
	CController::Update(aActor, aDT);
}

float CFuzzyLogicController::IsHealthy(CActor & aActor)
{
	float status = aActor.GetHealth();
	status /= 100.f;
	return status;
}

#include <iostream>
float CFuzzyLogicController::IsThreatened(CActor & aActor)
{
	const float MAX_THREAT_DIST = 450.f;
	float status = 1.f;
	if (aActor.CanSeeEnemy())
	{
		status = Math::Clamp(Math::Length(aActor.GetClosestEnemy()->GetPosition() - aActor.GetPosition()) / MAX_THREAT_DIST, 0.f, 1.f);
	}
	status = 1.f - status;
	std::cout << status << std::endl;
	
	return status;
}

float CFuzzyLogicController::IsConfident(CActor & aActor)
{
	return 0.5f;
}
