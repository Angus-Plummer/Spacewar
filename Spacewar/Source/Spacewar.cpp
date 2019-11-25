#include "GameInstance.h"
#include <stdio.h>

int main()
{
	// initialise and tick the game instance
	sf::Clock clock;
	GameInstance* activeGameInstance = new GameInstance();
	activeGameInstance->Initialise();
	sf::Time elapsed = clock.restart();
	while (activeGameInstance->GetIsRunning())
	{
		elapsed = clock.restart();
		activeGameInstance->Update(elapsed.asSeconds());
	}

	return 0;
}