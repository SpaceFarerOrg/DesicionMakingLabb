
#ifdef _DEBUG
#pragma comment(lib, "sfml-system-d")
#pragma comment(lib, "sfml-window-d")
#pragma comment(lib, "sfml-graphics-d")
#else
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-graphics")
#endif

#include <SFML\System\Clock.hpp>
#include "Game.h"
#include <ctime>

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	bool shouldRun = true;

	CGame game(shouldRun);
	game.Init();

	sf::Clock deltaTimer;
	float deltaTime = 0.f;

	while (shouldRun)
	{
		deltaTime = deltaTimer.getElapsedTime().asSeconds();
		deltaTimer.restart();
		game.Update(deltaTime);
		game.Render();
	}


	return 0;
}