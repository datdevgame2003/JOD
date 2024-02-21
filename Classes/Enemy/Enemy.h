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
	//void shootBullet(const Vec2& targetPosition);
	std::string getState(); 
	//void stopMoving();
protected:
	bool loadAnimations() override;

	Health* _healthCtrl;

	void onDie();
	//void update(float dt);
	void onEnter();
	bool callbackOnContactBegin(PhysicsContact& contact);
	void playDeathAnimation();
protected:
	//std::string getState();
	StateMachine* _stateMachine;
	Character* character;
};

#endif // !__ENEMY_H__
