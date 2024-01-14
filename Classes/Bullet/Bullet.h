#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Entity/Entity.h"

USING_NS_CC;

class Bullet : public Node
{
public:
	static Bullet* create(std::string bulletName);

	virtual bool init(std::string bulletName);

protected:
	Sprite* _model;
protected:
	bool callbackOnContactBegin(PhysicsContact& contact);

	CC_SYNTHESIZE(Entity*, _owner, Owner);
};

#endif // !__BULLET_H__