#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "StateMachine/StateMachine.h"
#include "Health/Health.h"

class Character : public Entity
{
public:
	static Character* create(EntityInfo* info);

	bool init(EntityInfo* info) override;
	void takeDamage(Entity* attacker);
protected:
	bool loadAnimations() override;
	bool callbackOnContactBegin(PhysicsContact& contact);
protected:
	StateMachine* _stateMachine;
protected:

	Health* _healthCtrl;

	void onDie();
	void onEnter();
};

#endif // !__CHARACTER_H__
