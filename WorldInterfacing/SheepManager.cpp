#include "SheepManager.h"

void CSheepManager::Init()
{
	mySheepCollection.reserve(100);
}

void CSheepManager::AddSheep(CActor & aSheep)
{
	mySheepCollection.push_back(&aSheep);
}

std::vector<CActor*>& CSheepManager::GetSheepCollection()
{
	return mySheepCollection;
}
