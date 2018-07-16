#include "AIEventManager.h"

void CAIEventManager::PostEvent(EAIEvents aEvent, const sf::Vector2f & aPosition)
{
	myEvents.push_back({ aEvent, aPosition });
}

void CAIEventManager::SubscribeToEvent(EAIEvents aEvent, std::function<void(const sf::Vector2f&)> aCallbackFunction)
{
	myCallbackFunctionsByEvent[(unsigned)aEvent].push_back(aCallbackFunction);
}

void CAIEventManager::DispatchEvents()
{
	for (SEvent& event : myEvents)
	{
		for (unsigned i = 0; i < myCallbackFunctionsByEvent[(unsigned)event.myEvent].size(); ++i)
		{
			myCallbackFunctionsByEvent[(unsigned)event.myEvent][i](event.myPosition);
		}
	}

	myEvents.clear();
}
