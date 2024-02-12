#include "EnemyDeadState.h"
#include "KeyboardInput.h"
#include "StateMachine/StateMachine.h"

void EnemyDeadState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()->getAnimation(_owner->getEntityInfo()->_entityName + "-dead");

	if (ani) {
		_owner->getModel()->stopAllActions();
		auto animate = RepeatForever::create(Animate::create(ani));
		animate->setTag(StateMachine::AnimationTag);
		_owner->getModel()->runAction(animate);
	}
}

std::string EnemyDeadState::updateState()
{
	return ("dead");
}
void EnemyDeadState::exitState()
{
	State::exitState();
}