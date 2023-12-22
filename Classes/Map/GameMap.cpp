#include "GameMap.h"

const std::string GameMap::Collidable = "Collidable";

GameMap* GameMap::create(const std::string& tmxFile)
{
	GameMap* ret = new (std::nothrow) GameMap();
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GameMap::initWithTMXFile(const std::string& tmxFile)
{
	if (!TMXTiledMap::initWithTMXFile(tmxFile))
	{
		log("Init GameMap failed!");
		return false;
	}

	_metaLayer = this->getLayer("Meta");
	if (_metaLayer)
		_metaLayer->setVisible(false);
	return true;
}

int GameMap::getMetaAtPos(const Vec2& position)
{
	Point posTile = convertPosTileMap(position);
	int result = -1;
	int tileGid = _metaLayer->getTileGIDAt(posTile);
	if (tileGid != 0)
	{
		Value temp = this->getPropertiesForGID(tileGid);
		if (!temp.isNull())
		{
			ValueMap properties = temp.asValueMap();
			auto properName = properties.find(GameMap::Collidable);
			auto properValue = properties.at(GameMap::Collidable).asInt();
			if (properName != properties.end() && properValue == GameMap::MetaRed)
			{
				result = GameMap::MetaRed;
			}
			else if (properName != properties.end() && properValue == GameMap::MetaGreen)
			{
				result = GameMap::MetaGreen;
			}
		}
	}

	return result;
}

Point GameMap::convertPosTileMap(Vec2 objectPos)
{
	int x = objectPos.x / _tileSize.width;
	int y = (this->getContentSize().height - objectPos.y) / _tileSize.height;
	return Point(x, y);
}