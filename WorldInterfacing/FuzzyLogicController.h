#pragma once
#include "Controller.h"

class CFuzzyLogicController : public CController
{
public:
	CFuzzyLogicController();
	~CFuzzyLogicController();

	void Update(CActor& aActor, float aDT) override;

private:

	short myDecision = 0;
	short myPrevDecision = 0;

	float IsHealthy(CActor& aActor);
	float IsThreatened(CActor& aActor);
	float IsConfident(CActor& aActor);
};
