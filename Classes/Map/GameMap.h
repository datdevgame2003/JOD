#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMap : public TMXTiledMap
{
public:
	static const std::string MapPath;
	static const std::string Collidable;
public:
	static GameMap* create(const std::string& tmxFile);
	bool initWithTMXFile(const std::string& tmxFile);

	static const int MetaRed = 0;
	static const int MetaGreen = 1;

	int getMetaAtPos(const Vec2& position);
	Point convertPosTileMap(Vec2 objectPos);

protected:
	TMXLayer* _metaLayer;
};

#endif // !__GAME_MAP_H__
