#ifndef __I_DAMAGEABLE_H__

#include "Entity/Entity.h"

// EnemySpawn

class IDamageable
{
public:
	virtual void takeDamage(Entity* attacker) {}
};

#endif // !__I_DAMAGEABLE_H__
