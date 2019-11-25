#pragma once
#include "../GameMode.h"
#include <map>

class World;
class BattleController;

enum BattleState
{
	Initialising,
	ReadyCheck,
	Playing,
	Paused,
	RoundOver,
	BattleOver,
	Quitting
};

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
	BattleState mState;
	float mStateTimer;
	World* mWorld;
	bool IsRoundOver() const;

	void SetupWorld();
};