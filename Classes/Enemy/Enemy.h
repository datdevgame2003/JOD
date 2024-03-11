#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity/Entity.h"
#include "IDamageable.h"
#include "Health/Health.h"
#include "StateMachine/StateMachine.h"
#include "Character/Character.h"
class Enemy : public Entity, public IDamageable
{
public:
	static Enemy* create(EntityInfo* info);
	virtual bool init(EntityInfo* info) override;

	void takeDamage(Entity* attacker) override;
	
	std::string getState(); 
	
protected:
	bool loadAnimations() override;

	Health* _healthCtrl;

	void onDie();
	
	void onEnter();
	bool callbackOnContactBegin(PhysicsContact& contact);
	void playDeathAnimation();
protected:
	StateMachine* _stateMachine;
	Character* character;
};

#endif // !__ENEMY_H__
