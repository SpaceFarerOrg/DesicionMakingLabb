#include "Button.h"
#include "Math.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "AIEventManager.h"

void CButton::Init(sf::Texture & aTexture, CAIEventManager* aEventManager)
{
	mySprite.setTexture(aTexture);

	ReInit();

	myRadius = mySprite.getGlobalBounds().width / 2.f;

	mySprite.setOrigin(mySprite.getGlobalBounds().width / 2.f, mySprite.getGlobalBounds().height / 2.f);

	myEventManager = aEventManager;

}

void CButton::ReInit()
{
	myPosition.x = (float)(rand() % 1400);
	myPosition.y = (float)(rand() % 700) + 200;
}

bool CButton::IsCollidingWith(const sf::Vector2f & aPosition, float aRadius)
{
	if (Math::Length2(myPosition - aPosition) < (aRadius * aRadius) + (myRadius * myRadius))
	{
		myHasCollidedThisFrame = true;

		//myEventManager->PostEvent(CAIEventManager::EAIEvents::ButtonPressed, myPosition);

		return true;
	}

	return false;
}

void CButton::Render(sf::RenderWindow * aWindow)
{
	mySprite.setPosition(myPosition);

	if (myHasCollidedThisFrame)
	{
		mySprite.setColor(sf::Color::Red);
	}
	else
	{
		mySprite.setColor(sf::Color::White);
	}
	
	myHasCollidedThisFrame = false;

	aWindow->draw(mySprite);


}

const sf::Vector2f & CButton::GetPosition()
{
	return myPosition;
}
