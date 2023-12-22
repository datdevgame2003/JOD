#include "CharacterRunState.h"
#include "StateMachine/StateMachine.h"
#include "KeyboardInput.h"

void CharacterRunState::enterState(Entity* owner)
{
	State::enterState(owner);
	auto ani = AnimationCache::getInstance()
		->getAnimation(_owner->getEntityInfo()->_entityName + "-run");
	auto animate = RepeatForever::create(Animate::create(ani));
	animate->setTag(StateMachine::AnimationTag);
	_owner->getModel()->runAction(animate);
	auto mapNode = Director::getInstance()->getRunningScene()->getChildByTag(99);
	if (mapNode != nullptr) {
		_map = dynamic_cast<GameMap*>(mapNode);
	}
}

std::string CharacterRunState::updateState()
{
	auto keyboard = KeyboardInput::getInstance();

	Vec2 direction = keyboard->getDirection();
	float dt = Director::getInstance()->getAnimationInterval();
	Vec2 nextPosition = _owner->getPosition() + direction * _owner->getEntityStat()->_runSpeed * dt;
	if (_map->getMetaAtPos(nextPosition) != GameMap::MetaRed)
		_owner->setPosition(nextPosition);

	/*if (_map->getMetaAtPos(nextPosition) == GameMap::MetaGreen)
		Director::getInstance()->replaceScene(GameWinScene::createScene());*/

	if (direction.x != 0)
		_owner->getModel()->setFlippedX(direction.x < 0);

	// 
	if (keyboard->getKey(EventKeyboard::KeyCode::KEY_SPACE))
	{
		return "attack";
	}

	if (keyboard->getDirection() == Vec2::ZERO)
	{
		return "idle";
	}
	return "run";
}

void CharacterRunState::exitState()
{
	State::exitState();
}