#include "GameScene.h"
#include "GameWinScene.h"
#include "GameOverScene.h"
#include "ui/CocosGUI.h"
#include "Menu.h"
#include "Enemy/Enemy.h"
#include "KeyboardInput.h"
#include "Map/GameMap.h"
#include "Camera/CameraFollow.h"
#include "audio/include/AudioEngine.h"
#include "Layer/SettingLayer.h"
#include "SettingScene.h"
#include "Bullet/Bullet.h"
USING_NS_CC;

Scene* GameScene::create(std::string mapName)
{
	auto newObject = new GameScene();
	if (newObject != nullptr && newObject->init(mapName))
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

bool GameScene::init(std::string mapName) {
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));

	auto winSize = Director::getInstance()->getWinSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::map<std::string, int> countdownTimeMap;
	countdownTimeMap["map1"] = 90;
	countdownTimeMap["map2"] = 120;
	countdownTimeMap["map3"] = 150;
	countdownTimeMap["map4"] = 180;
	if (countdownTimeMap.find(mapName) != countdownTimeMap.end())
	{
		initialCountdownTime = countdownTimeMap[mapName];
	}

	elapsedTime = 0.0f;
	Ended = false;


	timeLabel = Label::createWithTTF("Time: ", "fonts/Marker Felt.ttf", 30);
	timeLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
	timeLabel->enableGlow(Color4B::BLUE);
	timeLabel->enableOutline(Color4B::BLUE, 1);
	this->addChild(timeLabel, 100);


	layer = Layer::create();
	//EntityStat* characterStat = new EntityStat();
	//characterStat->_runSpeed = 200.0f;*/

	
	//character->setEntityStat(characterStat);


	_gameMap = GameMap::create(mapName);
	_gameMap->setTag(99);


	//enemy
	TMXObjectGroup* enemySpawnPoint = _gameMap->getObjectGroup("EnemySpawnPoint");
	auto enemies = enemySpawnPoint->getObjects();
	int baseEnemyLevel = 1;
	for (auto enemyInfo : enemies)
	{
		ValueMap entityInfo = enemyInfo.asValueMap();
		std::string name = entityInfo["name"].asString();
		/*int lv = entityInfo["level"].asInt();
		auto info = new EntityInfo(lv, name);*/

		int mapLevelModifier = 0;
		if (mapName == "map2") {
			mapLevelModifier = 1;
		}
		else if (mapName == "map3") {
			mapLevelModifier = 2;
		}
		else if (mapName == "map4") {
			mapLevelModifier = 3;
		}
		int enemyLevel = baseEnemyLevel + mapLevelModifier;
	    //auto enemy = Enemy::create(new EntityInfo(3, "slime"));
		Vec2 position;
		position.x = entityInfo["x"].asFloat();
		position.y = entityInfo["y"].asFloat();
		//auto enemy = Enemy::create(info);
		auto enemy = Enemy::create(new EntityInfo(enemyLevel, "slime"));
		enemy->setPosition(position);
		this->addChild(enemy, 3);
	}


	//Character
	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("Nv");
	character = Character::create(new EntityInfo(1, "Boy"));

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	character->setPosition(position);
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode key, Event* event) {
		if (key == EventKeyboard::KeyCode::KEY_TAB)
		{
			log("character level up");

			character->setLevel(character->getEntityInfo()->_level + 1);

		}
	};

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->setSwallowTouches(true);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->addChild(_gameMap);
	this->addChild(layer, 100);
	this->addChild(character, 1);


	auto buttonSetting = ui::Button::create("setting.png");
	buttonSetting->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				Director::getInstance()->pause();
				auto layer = SettingLayer::create();
				this->addChild(layer, 101);
				
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonSetting->setPosition(Vec2(visibleSize.width / 20, visibleSize.height * 0.9));
	buttonSetting->setScale(visibleSize.height / buttonSetting->getContentSize().height * 0.1);
	layer->addChild(buttonSetting);
	auto moveUp = ui::Button::create("w.png");
	moveUp->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				KeyboardInput::getInstance()->onKeyPressed(EventKeyboard::KeyCode::KEY_W, nullptr);
				break;
			case ui::Widget::TouchEventType::ENDED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_W, nullptr);
				break;
			case ui::Widget::TouchEventType::CANCELED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_W, nullptr);
				break;
			default:
				break;
			}
		});

	moveUp->setPosition(Vec2(visibleSize.width / 2 - 500, visibleSize.height / 2 - 190));
	moveUp->setScale(2);
	moveUp->setOpacity(80);//0-255
	layer->addChild(moveUp,10);
	auto moveLeft = ui::Button::create("a.png");
	moveLeft->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				KeyboardInput::getInstance()->onKeyPressed(EventKeyboard::KeyCode::KEY_A, nullptr);
				break;
			case ui::Widget::TouchEventType::ENDED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_A, nullptr);
			case ui::Widget::TouchEventType::CANCELED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_A, nullptr);
				break;
			default:
				break;
			}
		});

	moveLeft->setPosition(Vec2(visibleSize.width / 2 - 580, visibleSize.height / 2 - 270));
	moveLeft->setScale(2);
	moveLeft->setOpacity(80);//0-255
	layer->addChild(moveLeft);
	auto moveRight = ui::Button::create("d.png");
	moveRight->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				KeyboardInput::getInstance()->onKeyPressed(EventKeyboard::KeyCode::KEY_D, nullptr);
				break;
			case ui::Widget::TouchEventType::ENDED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_D, nullptr);
			case ui::Widget::TouchEventType::CANCELED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_D, nullptr);
				break;
			default:
				break;
			}
		});

	moveRight->setPosition(Vec2(visibleSize.width / 2 - 420, visibleSize.height / 2 - 270));
	moveRight->setScale(2);
	moveRight->setOpacity(80);//0-255
	layer->addChild(moveRight);
	auto moveDown = ui::Button::create("s.png");
	moveDown->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				KeyboardInput::getInstance()->onKeyPressed(EventKeyboard::KeyCode::KEY_S, nullptr);
				break;
			case ui::Widget::TouchEventType::ENDED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_S, nullptr);
			case ui::Widget::TouchEventType::CANCELED:
				KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_S, nullptr);
				break;
			default:
				break;
			}
		});

	moveDown->setPosition(Vec2(visibleSize.width / 2 - 500, visibleSize.height / 2 - 350));
	moveDown->setScale(2);
	moveDown->setOpacity(80);//0-255
	layer->addChild(moveDown);

	//auto attack = ui::Button::create("attack.png");
	//attack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	//	{
	//		switch (type)
	//		{
	//		case ui::Widget::TouchEventType::BEGAN:
	//			KeyboardInput::getInstance()->onKeyPressed(EventKeyboard::KeyCode::KEY_SPACE, nullptr);
	//			break;
	//		case ui::Widget::TouchEventType::ENDED:
	//			KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_SPACE, nullptr);
	//		case ui::Widget::TouchEventType::CANCELED:
	//			KeyboardInput::getInstance()->onKeyReleased(EventKeyboard::KeyCode::KEY_SPACE, nullptr);
	//			break;
	//		default:
	//			break;
	//		}
	//	});

	//attack->setPosition(Vec2(visibleSize.width / 2 + 500, visibleSize.height / 2 - 270));
	//attack->setScale(2);
	//attack->setOpacity(80);//0-255
	//layer->addChild(attack,99);
	this->scheduleUpdate();
	this->schedule([=](float dt) {
		updateTime(dt);
		}, 1.0f, "updateTime");

	return true;
}
void GameScene::update(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	layer->setPosition(this->getDefaultCamera()->getPosition() + visibleSize / -2);
	timeLabel->setPosition(this->getDefaultCamera()->getPosition() + visibleSize / 3);
}

void GameScene::updateTime(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	elapsedTime += 1.0f;
	int remainingTime = static_cast<int>(initialCountdownTime - elapsedTime);
	remainingTime = std::max(remainingTime, 0);
	timeLabel->setString(StringUtils::format("Time: %d", remainingTime));

}

void GameScene::onEnter()
{
	Scene::onEnter();
	if (KeyboardInput::getInstance()->getParent() != nullptr)
		KeyboardInput::getInstance()->removeFromParent();
	Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto mapSize = _gameMap->getContentSize();
	Rect boundingBox = { size.width / 2,size.height / 2,mapSize.width - size.width / 2 - size.width / 2,mapSize.height - size.height / 2 - size.height / 2 };
	CameraFollow* cam = CameraFollow::create(character, boundingBox);
	this->addChild(cam);

	this->addChild(KeyboardInput::getInstance());
}
bool GameScene::onTouchBegan(Touch* touch, Event* event)
{

	Vec2 touchPos = touch->getLocation();
	Vec2 characterPos = character->getPosition();
	Vec2 direction = touchPos - characterPos;
	direction.normalize();
	auto bullet = Bullet::create("pumpum");
	bullet->setPosition(characterPos);
	bullet->getPhysicsBody()->setVelocity(direction * 300);
	bullet->setOwner(character);
	this->addChild(bullet, 1);
	return true;
}
bool GameScene::checkWinCondition()
{
	if (!Ended)

		if (elapsedTime <= initialCountdownTime)
		{
			Vec2 characterTilePos = _gameMap->convertPosTileMap(character->getPosition());

			if (_gameMap->getMetaAtPos(characterTilePos) == GameMap::MetaGreen)
			{

				CCLOG("You win");
				this->removeChild(character);
				character = nullptr;
				auto gamewinScene = GameWinScene::create();
				Director::getInstance()->replaceScene(gamewinScene);
				//Director::getInstance()->replaceScene(GameWinScene::createScene());
				Ended = true;
				return true;

			}
		}


	//if (elapsedTime > 30.0f)
	//{
	//	CCLOG("You lose!");
	//	//this->removeChild(character);
	//	//character = nullptr;

	//	//Director::getInstance()->replaceScene(GameOverScene::createScene());
	//	Ended = true;
	//	return true;

	//}
	return false;

}

