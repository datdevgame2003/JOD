#include "EnemyAttackState.h"
#include "StateMachine/StateMachine.h"

void EnemyAttackState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-attack");
	auto animate = Animate::create(ani);
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string EnemyAttackState::updateState()
{
	// updade 

	// check
	auto animation = _owner->getModel()->getActionByTag(StateMachine::AnimationTag);
	if (animation == nullptr || animation->isDone()) {
		return "idle";
	}
	return "attack";
}

void EnemyAttackState::exitState()
{
	State::exitState();
}
