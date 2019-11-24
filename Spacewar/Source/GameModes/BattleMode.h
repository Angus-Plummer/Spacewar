#pragma once
#include "GameMode.h"

class World;

class BattleMode : public GameMode
{
public:
	BattleMode(int numPlayers);
	~BattleMode();

	virtual void Initialise() override;
	virtual void Update(const float deltaTime) override;

	World* GetWorld() const;

protected:
	World* mWorld;
};