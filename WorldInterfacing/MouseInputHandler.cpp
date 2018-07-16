#include "MouseInputHandler.h"
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

sf::RenderWindow* CMouseInputHandler::ourRelativeWindow = nullptr;

void CMouseInputHandler::SetWindowToGetRelativePositionTo(sf::RenderWindow * aWindow)
{
	ourRelativeWindow = aWindow;
}

bool CMouseInputHandler::IsClickRegistered() const
{
	return myIsClickRegistered;
}

void CMouseInputHandler::UpdateMousePos()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		myIsClickRegistered = true;
		myClickPosition = { (float)sf::Mouse::getPosition(*ourRelativeWindow).x, (float)sf::Mouse::getPosition(*ourRelativeWindow).y };
	}
}

const sf::Vector2f & CMouseInputHandler::GetClickPosition()
{
	return myClickPosition;
}
