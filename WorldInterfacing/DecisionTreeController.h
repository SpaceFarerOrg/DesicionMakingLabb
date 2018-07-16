#pragma once
#include "Controller.h"
class CDecisionTreeController : public CController
{
public:
	CDecisionTreeController();
	~CDecisionTreeController();

	void Update(CActor& aActor, float aDT) override;

private:
	short myDecision;
	short myPrevDecision;
};

