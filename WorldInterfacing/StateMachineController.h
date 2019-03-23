#pragma once
#include "Controller.h"
class CStateMachineController : public CController
{
public:

	enum class EState
	{
		Attack,
		Idle,
		SeekHealth,
		SeekPowerUp,
		Count
	};

	CStateMachineController();
	~CStateMachineController();

	void Update(CActor& aActor, float aDT) override;

private:
	EState myState;
	EState myPreviousState;
};

