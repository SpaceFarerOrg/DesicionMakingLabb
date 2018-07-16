#include "PollingStation.h"
#include "SheepManager.h"

void CPollingStation::Init(std::function<const sf::Vector2f&()> aGetPlayerPositionFunction)
{
	myGetPlayerPositionFunction = aGetPlayerPositionFunction;
	myCurrentFrame = 0;
}

void CPollingStation::RegisterFunction(EPollableValue aValueTag, std::function<const sf::Vector2f&()> aFunctionToCall)
{
	SPollFunc pf;
	pf.myFunc = aFunctionToCall;
	pf.myLastUpdated = 0;
	pf.polledValue = { 0,0 };
	myRegisteredFunctions[(unsigned)aValueTag] = pf;
}

const sf::Vector2f & CPollingStation::PollValue(CPollingStation::EPollableValue aValueTag)
{
	if (myRegisteredFunctions[(unsigned)aValueTag].myLastUpdated < myCurrentFrame)
		myRegisteredFunctions[(unsigned)aValueTag].polledValue = myRegisteredFunctions[(unsigned)aValueTag].myFunc();

	return myRegisteredFunctions[(unsigned)aValueTag].polledValue;
}


void CPollingStation::RegisterSheepManager(CSheepManager * aSheepManager)
{
	mySheepManager = aSheepManager;
}

std::vector<class CActor*>& CPollingStation::GetSheepCollection()
{
	return mySheepManager->GetSheepCollection();
}

void CPollingStation::BeginFrame()
{
	++myCurrentFrame;
}

const sf::Vector2f & CPollingStation::GetPlayerPosition()
{
	if (myPlayerPosition.myLastUpdated < myCurrentFrame)
		UpdatePlayerPosition();

	return myPlayerPosition.myValue;
}

void CPollingStation::UpdatePlayerPosition()
{
	myPlayerPosition.myLastUpdated = myCurrentFrame;
	myPlayerPosition.myValue = myGetPlayerPositionFunction();
}
