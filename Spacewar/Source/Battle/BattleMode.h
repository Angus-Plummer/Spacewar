#pragma once
#include "../GameMode.h"
#include <map>

class World;
class BattleController;

class BattleMode : public GameMode
{
public:
	BattleMode(int numPlayers);
	~BattleMode();

	virtual void Initialise() override;
	virtual void Update(const float deltaTime) override;

	World* GetWorld() const;

	BattleController* GetBattleController(int id) const;

protected:
	World* mWorld;
};