#ifndef __ENTITY_INFO_H__
#define __ENTITY_INFO_H__

#include <iostream>
#include <string>
#include "Map/GameMap.h"
class EntityInfo
{
public:
	int _level;
	std::string _entityName;
	std::string mapName;
	EntityInfo(int level, std::string name)
	{
		this->_entityName = name;
		this->_level = level;
		
	}
};

#endif // !__ENTITY_INFO_H__