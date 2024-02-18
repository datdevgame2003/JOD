#include "Enemy/Enemy.h"
#include "Character/Character.h"
#include "Utilities/AnimationUtils.h"
#include "DefineBitmask.h"
#include "StateEnemy/EnemyIdleState.h"
#include "StateEnemy/EnemyAttackState.h"
#include "StateEnemy/EnemyDeadState.h"
#include "Bullet/Bullet.h"
Enemy* Enemy::create(EntityInfo* info)
{
	auto newObject = new Enemy();
	if (newObject != nullptr && newObject->init(info))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Enemy::init(EntityInfo* info)
{
	if (!Entity::init(info))
	{
		log("Init Enemy failed!");
		return false;
	}

	_model = Sprite::createWithSpriteFrameName(_info->_entityName + "-idle (1)");
	this->addChild(_model);

	_stateMachine = StateMachine::create(this);
	_stateMachine->addState("idle", new EnemyIdleState());
	_stateMachine->addState("attack", new EnemyAttackState());
	_stateMachine->addState("dead", new EnemyDeadState());
	_stateMachine->setCurrentState("idle");

	auto lvLabel = Label::createWithSystemFont("Lv. " + std::to_string(info->_level)
		, "Arial", 16);
	lvLabel->setAlignment(TextHAlignment::LEFT);

	lvLabel->setPositionX(_model->getPosition().x + 8);

	this->addChild(lvLabel);


	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1), 1.0f);
	body->setCategoryBitmask(DefineBitmask::Enemy);
	body->setCollisionBitmask(DefineBitmask::Character); 
	body->setContactTestBitmask(DefineBitmask::Character);
	this->setPhysicsBody(body);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Enemy::callbackOnContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->addChild(_stateMachine);

	return true;
}

void Enemy::takeDamage(Entity* attacker)
{
	int dame = attacker->getEntityStat()->_attack;
	log("take dame: %d", dame);
	_healthCtrl->setCurrentHealth(_healthCtrl->getCurrentHealth() - dame);
}

bool Enemy::loadAnimations()
{
	Entity::loadAnimations();

	std::vector<std::string> aniNames;
	aniNames.push_back(_info->_entityName + "-idle");
	aniNames.push_back(_info->_entityName + "-attack");
	aniNames.push_back(_info->_entityName + "-dead");

	for (auto name : aniNames)
	{
		AnimationUtils::loadSpriteFrameCache("Enemy/", name);
		AnimationUtils::createAnimation(name, 1.0f);
	}

	return true;
}

void Enemy::onDie()
{
	log("die");
	// add effects....
	playDeathAnimation();
	/*this->removeFromParentAndCleanup(true);*/
}

void Enemy::onEnter()
{
	Node::onEnter();

	// health
	_healthCtrl = Health::create(_entityStat->_health, "_hp.png");
	_healthCtrl->setOnDie(CC_CALLBACK_0(Enemy::onDie, this));
	_healthCtrl->setPosition(Vec2(-_healthCtrl->getContentSize().width / 2
		, _model->getContentSize().height));
	this->addChild(_healthCtrl);
}

bool Enemy::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;
	log("call at enemy");
	return false;
}
//void Enemy::shootBullet(const Vec2& targetPosition)
//{
//	//Vec2 bulletDirection = targetPosition - this->getPosition();
//	//bulletDirection.normalize();
//	auto bullet = Bullet::create("pumchiu");
//	bullet->setPosition(this->getPosition());
//	Vec2 direction = targetPosition - bullet->getPosition();
//	direction.normalize();
//	float bulletSpeed = 500.0f;
//	bullet->getPhysicsBody()->setVelocity(direction * bulletSpeed);
//	this->getParent()->addChild(bullet, 1);
//}

void Enemy::playDeathAnimation() {
	auto ani = AnimationCache::getInstance()->getAnimation(_info->_entityName + "-dead");
	if (ani) {
		_model->stopAllActions();
		auto animate = RepeatForever::create(Animate::create(ani));
		animate->setTag(StateMachine::AnimationTag);
		_model->runAction(animate);
	}
	auto delay = DelayTime::create(2.0f);
	auto callback = CallFunc::create([this]() {
		this->removeFromParentAndCleanup(true);
		});

	auto sequence = Sequence::create(delay, callback, nullptr);
	_model->runAction(sequence);
}
//void Enemy::update(float dt) {
//	// Gọi phương thức cơ bản của lớp Entity
//	Entity::update(dt);
//
//	Vec2 characterPosition = character->getPosition();
//	float distance = this->getPosition().distance(characterPosition);
//
//	// Nếu khoảng cách nhỏ hơn một ngưỡng nhất định (ví dụ: 200px)
//	if (distance < 200.0f) {
//		// Bắn đạn
//		this->shootBullet(characterPosition);
//	}
//}
