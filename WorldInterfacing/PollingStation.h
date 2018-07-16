#pragma once
#include <SFML\System\Vector2.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

class CPollingStation
{
public:
	enum class EPollableValue
	{
		latestClickedPos,
		arriverPos,
	};

public:
	void Init(std::function<const sf::Vector2f&()> aGetPlayerPositionFunction);
	void RegisterFunction(EPollableValue aValueTag, std::function<const sf::Vector2f&()> aFunctionToCall);
	const sf::Vector2f& PollValue(EPollableValue aValueTag);

	void RegisterSheepManager(class CSheepManager* aSheepManager);
	std::vector<class CActor*>& GetSheepCollection();

	void BeginFrame();
	const sf::Vector2f& GetPlayerPosition();
private:
	struct SPollFunc
	{
		std::function<const sf::Vector2f&()> myFunc;
		sf::Vector2f polledValue;
		unsigned int myLastUpdated;
	};


	CSheepManager* mySheepManager;
	std::function<const sf::Vector2f&()> myGetPlayerPositionFunction;
	std::unordered_map<unsigned, SPollFunc> myRegisteredFunctions;

	void UpdatePlayerPosition();

	unsigned int myCurrentFrame;

	struct SPlayerPositionCache
	{
		sf::Vector2f myValue;
		unsigned int myLastUpdated;
	} myPlayerPosition;
};