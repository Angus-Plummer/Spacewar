#include "GameInstance.h"
#include <stdio.h>

int main()
{
	// initialise and tick the game instance
	sf::Clock clock;
	GameInstance* activeGameInstance = new GameInstance();
	activeGameInstance->Initialise();

	while (activeGameInstance->GetIsRunning())
	{
		sf::Time elapsed = clock.restart();
		activeGameInstance->Update(elapsed.asSeconds());
	}

	return 0;
}