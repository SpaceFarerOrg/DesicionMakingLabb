#pragma once
#include <vector>

class CActor;

class CSheepManager
{
public:
	void Init();
	void AddSheep(CActor& aSheep);

	std::vector<CActor*>& GetSheepCollection();
private:
	std::vector<CActor*> mySheepCollection;
};