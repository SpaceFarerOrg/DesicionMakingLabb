#pragma once
#include <SFML\System\Vector2.hpp>

namespace sf
{
	class RenderWindow;
}

class CMouseInputHandler
{
public:
	static void SetWindowToGetRelativePositionTo(sf::RenderWindow* aWindow);
	CMouseInputHandler() = default;

	bool IsClickRegistered() const;
	void UpdateMousePos();
	const sf::Vector2f& GetClickPosition();

private:
	bool myIsClickRegistered;
	sf::Vector2f myClickPosition;
	static sf::RenderWindow* ourRelativeWindow;
};