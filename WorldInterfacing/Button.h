#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

namespace sf
{
	class RenderWindow;
}

class CButton
{
public:
	void Init(sf::Texture& aTexture, class CAIEventManager* aEventManager);
	void ReInit();
	bool IsCollidingWith(const sf::Vector2f& aPosition, float aRadius);
	void Render(sf::RenderWindow* aWindow);

	const sf::Vector2f& GetPosition();
private:
	CAIEventManager* myEventManager;

	sf::Sprite mySprite;
	sf::Vector2f myPosition;
	float myRadius;

	bool myHasCollidedThisFrame;

};