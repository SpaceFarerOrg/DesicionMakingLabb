#pragma once
#include <SFML\System\Vector2.hpp>
#include <functional>
#include <vector>
#include <array>

class CAIEventManager
{
public:
	enum class EAIEvents
	{
		ButtonPressed,
		Count
	};
public:
	void PostEvent(EAIEvents aEvent, const sf::Vector2f& aPosition);
	void SubscribeToEvent(EAIEvents aEvent, std::function<void(const sf::Vector2f&)> aCallbackFunction);

	void DispatchEvents();
private:
	struct SEvent
	{
		EAIEvents myEvent;
		sf::Vector2f myPosition;
	};

	std::vector<SEvent> myEvents;
	std::array <std::vector<std::function<void(const sf::Vector2f&)>>, (unsigned)EAIEvents::Count> myCallbackFunctionsByEvent;
};