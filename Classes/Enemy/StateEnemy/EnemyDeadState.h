#ifndef __ENEMY_DEAD_STATE_H__
#define __ENEMY_DEAD_STATE_H__

#include "StateMachine/State.h"

class EnemyDeadState : public State
{
public:
	void enterState(Entity* owner) override;
	std::string updateState() override;
	void exitState() override;
};

#endif // !__ENEMY_DEAD_STATE_H__