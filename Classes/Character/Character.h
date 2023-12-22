#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"

class Character : public Entity
{
public:
	static Character* create(EntityInfo* info);

	bool init(EntityInfo* info) override;

protected:
	bool loadAnimations() override;
protected:
	StateMachine* _stateMachine;
};

#endif // !__CHARACTER_H__
