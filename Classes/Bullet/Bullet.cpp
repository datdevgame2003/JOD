#include "Bullet.h"
#include "DefineBitmask.h"
#include "IDamageable.h"

Bullet* Bullet::create(std::string bulletName)
{
	auto newObject = new Bullet();
	if (newObject != nullptr && newObject->init(bulletName))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool Bullet::init(std::string bulletName)
{
	if (!Node::init())
	{
		log("init Bullet failed!");
		return false;
	}

	_model = Sprite::create("Bullet/" + bulletName + ".png");
	this->addChild(_model);

	auto body = PhysicsBody::createEdgeBox(_model->getContentSize(), PhysicsMaterial(1, 0, 1), 1.0f);
	body->setCategoryBitmask(DefineBitmask::Bullet);
	body->setCollisionBitmask(DefineBitmask::NON);
	body->setContactTestBitmask(DefineBitmask::Character | DefineBitmask::Enemy);
	//body->setContactTestBitmask(DefineBitmask::Enemy| DefineBitmask::Character);

    this->setPhysicsBody(body);

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(Bullet::callbackOnContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool Bullet::callbackOnContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA != this && nodeB != this) return false;

	auto target = (nodeA == this) ? (nodeB) : (nodeA);
	//auto gameMap = dynamic_cast<GameMap*>(target->getParent());
	//if (gameMap != nullptr)
	//{
	//	// Chuyển đổi vị trí thế giới của đạn sang vị trí cục bộ trên GameMap
	//	Vec2 worldPos = this->getParent()->convertToWorldSpace(this->getPosition());
	//	Vec2 localPos = gameMap->convertToNodeSpace(worldPos);
	//	int metaType = gameMap->getMetaAtPos(localPos);

	//	// Kiểm tra xem tile có thuộc tính MetaRed không
	//	if (metaType == GameMap::MetaRed)
	//	{
	//		this->removeFromParentAndCleanup(true);
	//		return true; // Kết thúc phương thức
	//	}
	//}
	log("a: %d | b: %d", nodeA->getPhysicsBody()->getCategoryBitmask()
		, nodeB->getPhysicsBody()->getCategoryBitmask());
	log("a & b: %d", (nodeA->getPhysicsBody()->getCategoryBitmask() | nodeB->getPhysicsBody()->getCategoryBitmask()));

	auto damageable = dynamic_cast<IDamageable*>(target);
	if (damageable != nullptr)
	{
		damageable->takeDamage(_owner);
	}

	this->removeFromParentAndCleanup(true);
	//nodeA->removeFromParentAndCleanup(true);
	return false;
}