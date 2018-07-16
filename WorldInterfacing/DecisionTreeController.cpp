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
	/* Here be code for behaviour switching :D */

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
			myDecision = 1;
			if (myDecision != myPrevDecision)
			{
				SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
			}
			aActor.GetWeapon()->AimAt(aActor.GetClosestEnemy()->GetPosition());
			aActor.GetWeapon()->Shoot();
			aActor.SetTarget(aActor.GetClosestEnemy()->GetPosition());
		}
		else
		{
			myDecision = 2;
			if (myDecision != myPrevDecision)
			{
				SetSteeringBehaviour(new CWander());
			}
		}
	}

	myPrevDecision = myDecision;
	CController::Update(aActor, aDT);
}
