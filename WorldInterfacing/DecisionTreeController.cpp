#include "DecisionTreeController.h"
#include "SteeringBehaviours.h"
#include "Actor.h"


CDecisionTreeController::CDecisionTreeController()
{
}


CDecisionTreeController::~CDecisionTreeController()
{
}

void CDecisionTreeController::Update(CActor & aActor, float aDT)
{
	float health = aActor.GetHealth();
	bool canSeeEnemy = aActor.CanSeeEnemy();

	if (health <= 25)
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
	else
	{
		if (canSeeEnemy)
		{
			float distToEnemy = Math::Length(aActor.GetPosition() - aActor.GetClosestEnemy()->GetPosition());
			if (distToEnemy > 50.f && distToEnemy < 150.f)
			{
				myDecision = 1;
				if (myDecision != myPrevDecision)
				{
					SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
				}
			}
			else if (distToEnemy > 150.f)
			{
				myDecision = 4;
				aActor.SetTarget(aActor.GetPowerUpLocation());
				if (myDecision != myPrevDecision)
				{
					SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
				}
			}
			else
			{
				myDecision = 2;
				if (myDecision != myPrevDecision)
				{
					SetSteeringBehaviour(new CFlee(myBehaviour->GetPollingStation()));
				}
			}

			aActor.GetWeapon()->AimAt(aActor.GetClosestEnemy()->GetPosition());
			aActor.GetWeapon()->Shoot();
			aActor.SetTarget(aActor.GetClosestEnemy()->GetPosition());
		}
		else if (!aActor.IsGod())
		{
			myDecision = 5;
			aActor.SetTarget(aActor.GetPowerUpLocation());
			if (myDecision != myPrevDecision)
			{
				SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
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
	}

	myPrevDecision = myDecision;
	CController::Update(aActor, aDT);
}
