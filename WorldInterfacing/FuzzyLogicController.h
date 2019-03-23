#pragma once
#include "Controller.h"
class CFuzzyLogicController : public CController
{
public:
	CFuzzyLogicController();
	~CFuzzyLogicController();

	void Update(CActor& aActor, float aDT) override;

private:
};
