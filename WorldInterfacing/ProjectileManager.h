#pragma once
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

namespace sf
{
	class RenderWindow;
}

class CProjectileManager
{
public:

	struct SProjetile
	{
		sf::Vector2f myPosition;
		sf::Vector2f myDirection;
		float mySpeed;
		int myIDToIgnore;
	};

	static CProjectileManager& GetInstance();

	void Update(float aDT);
	void Render(sf::RenderWindow* aRenderWindow);
	void SpawnProjectile(const SProjetile& aProjectile);

	bool CheckCollisionAgainst(const sf::Vector2f& aPos, float aRadius, int aID);

private:

	CProjectileManager();
	~CProjectileManager();

	sf::Texture myProjectileTexture;
	sf::Sprite myProjectileSprite;

	std::vector<SProjetile> myProjectiles;
	int myIndex;
};

