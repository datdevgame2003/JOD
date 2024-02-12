#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity/Entity.h"
#include "IDamageable.h"
#include "Health/Health.h"
#include "StateMachine/StateMachine.h"

class Enemy : public Entity, public IDamageable
{
public:
	static Enemy* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;

	void takeDamage(Entity* attacker) override;
	void attack();
protected:
	bool loadAnimations() override;

	Health* _healthCtrl;

	void onDie();

	void onEnter();
	bool callbackOnContactBegin(PhysicsContact& contact);
	void playDeathAnimation();
protected:
	StateMachine* _stateMachine;
};

#endif // !__ENEMY_H__
