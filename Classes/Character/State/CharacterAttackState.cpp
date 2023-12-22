#include "CharacterAttackState.h"
#include "StateMachine/StateMachine.h"

void CharacterAttackState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-attack");
	auto animate = Animate::create(ani);
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string CharacterAttackState::updateState()
{
	// updade 

	// check
	auto animation = _owner->getModel()->getActionByTag(StateMachine::AnimationTag);
	if (animation == nullptr || animation->isDone()) {
		return "idle";
	}
	return "attack";
}

void CharacterAttackState::exitState()
{
	State::exitState();
}
