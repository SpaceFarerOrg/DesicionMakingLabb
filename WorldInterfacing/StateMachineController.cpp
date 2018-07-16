#include "StateMachineController.h"
#include "SteeringBehaviours.h"
#include "Actor.h"

CStateMachineController::CStateMachineController()
{
	myState = EState::Idle;
}


CStateMachineController::~CStateMachineController()
{
}

void CStateMachineController::Update(CActor & aActor, float aDT)
{

	EState newState = myState;

	switch (myState)
	{
	case EState::SeekHealth:
	{
		if (aActor.GetHealth() >= 100)
		{
			newState = EState::Idle;
		}
		else if (aActor.FindClosestHealthPickup())
		{
			if (myState != myPreviousState)
			{
				SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
			}
		}
	}
		break;
	case EState::Attack:
	{
		if (aActor.GetHealth() <= 25)
			newState = EState::SeekHealth;
		if (aActor.CanSeeEnemy() == false)
			newState = EState::Idle;
		else
		{
			if (myState != myPreviousState)
			{
				SetSteeringBehaviour(new CArrive(myBehaviour->GetPollingStation()));
			}
		}

		aActor.GetWeapon()->AimAt(aActor.GetClosestEnemy()->GetPosition());
		aActor.GetWeapon()->Shoot();
		aActor.SetTarget(aActor.GetClosestEnemy()->GetPosition());
	}
		break;
	case EState::Idle:
	{
		if (aActor.GetHealth() <= 25)
			newState = EState::SeekHealth;
		else if (aActor.CanSeeEnemy())
			newState = EState::Attack;
		else if (myState != myPreviousState)
			SetSteeringBehaviour(new CWander());
	}
		break;
	}

	myPreviousState = myState;
	myState = newState;

	CController::Update(aActor, aDT);
}
