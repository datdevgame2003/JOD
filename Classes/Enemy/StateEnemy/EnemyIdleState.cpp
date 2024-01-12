#include "EnemyIdleState.h"
#include "KeyboardInput.h"
#include "StateMachine/StateMachine.h"

void EnemyIdleState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-idle");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
}

std::string EnemyIdleState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();

	/*if (keyboard->getKey(EventKeyboard::KeyCode::KEY_SPACE))
	{
		return "attack";
	}*/

	/*if (keyboard->getDirection() != Vec2::ZERO)
	{
		return "run";
	}*/

	return "idle";
}

void EnemyIdleState::exitState()
{
	State::exitState();
}