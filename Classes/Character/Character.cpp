#include "Character.h"
#include "Utilities/AnimationUtils.h"
#include "State/CharacterIdleState.h"
#include "State/CharacterAttackState.h"
#include "State/CharacterRunState.h"

Character* Character::create(EntityInfo* info)
{
	auto newObject = new Character();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Character::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Character failed!");
		return false;
	}

	_model = Sprite::createWithSpriteFrameName(_info->_entityName + "-idle (2)");
	this->addChild(_model);

	_stateMachine = StateMachine::create(this);
	_stateMachine->addState("idle", new CharacterIdleState());
	_stateMachine->addState("run", new CharacterRunState());
	_stateMachine->addState("attack", new CharacterAttackState());
	_stateMachine->setCurrentState("idle");


	this->addChild(_stateMachine);
	return true;
}

bool Character::loadAnimations()
{
	Entity::loadAnimations();

	std::vector<std::string> aniNames;
	aniNames.push_back(_info->_entityName + "-idle");
	aniNames.push_back(_info->_entityName + "-run");
	aniNames.push_back(_info->_entityName + "-attack");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Character/", name);
		AnimationUtils::createAnimation(name, 1.0f);
	}

	return true;
}