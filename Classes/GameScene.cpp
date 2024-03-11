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
#include "AudioEngine.h"
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

bool GameScene::init(std::string mapName)
{
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
	//auto winSize = Director::getInstance()->getWinSize();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bGM = AudioEngine::play2d("Audio/BGM.mp3", false, 1.0f);
	AudioEngine::setFinishCallback(bGM, [=](int audioId, const std::string& filePath)
		{
			bGM = AudioEngine::play2d("Audio/BGM.mp3", false, 1.0f);
		});

	std::map<std::string, int> countdownTimeMap;
	countdownTimeMap["map1"] = 60;
	countdownTimeMap["map2"] = 5;
	countdownTimeMap["map3"] = 90;
	countdownTimeMap["map4"] = 120;
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
		//auto enemy = Enemy::create(info);
		Vec2 position;
		position.x = entityInfo["x"].asFloat();
		position.y = entityInfo["y"].asFloat();
		auto enemy = Enemy::create(new EntityInfo(enemyLevel, "slime"));
		enemy->setPosition(position);
		this->addChild(enemy, 22);
	}
	//character
	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("Nv");
	character = Character::create(new EntityInfo(1, "Boy"));
	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	character->setPosition(position);
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->setSwallowTouches(true);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(_gameMap);
	this->addChild(character, 1);
	this->addChild(layer, 100);
	this->scheduleUpdate();


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
	buttonSetting->setPosition(Vec2(visibleSize.width / 2 + 550, visibleSize.height / 2 + 350));
	buttonSetting->setScale(visibleSize.height / buttonSetting->getContentSize().height * 0.1);
	layer->addChild(buttonSetting, 99);


	auto button1 = ui::Button::create("back.png");
	button1->setTitleText("Back");
	button1->setTitleFontName("fonts/victoria.ttf");
	button1->setTitleFontSize(40);
	button1->setTitleColor(Color3B::BLACK);
	button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				clickAudio = AudioEngine::play2d("Audio/click.mp3");
				break;
			case ui::Widget::TouchEventType::ENDED:
				CCLOG("Button 1 clicked!");
				Director::getInstance()->replaceScene(TransitionFade::create(1, MenuScene::create()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}
		});
	button1->setPosition(Vec2(visibleSize.width / 2 - 550, visibleSize.height / 2 + 350));
	button1->setScale(1.5);
	layer->addChild(button1);
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
	layer->addChild(moveUp);
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

	//sound
	attackSoundPlayed = false;

	this->scheduleUpdate();
	this->schedule([=](float dt) {updateTime(dt);}, 1.0f, "updateTime");
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
	checkWinCondition();
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
	if (!attackSoundPlayed)
	{
		soundAttack = AudioEngine::play2d("Audio/attack.mp3", false, 1.0f);
		CCLOG("Attack Sound ID: %d", soundAttack);
		attackSoundPlayed = true;
		this->scheduleOnce([this](float dt) {
			attackSoundPlayed = false;
			}, 0.1f, "resetAttackSound");
		Vec2 touchPos = touch->getLocation();
		Vec2 characterPos = character->getPosition();
		Vec2 direction = touchPos - characterPos;
		direction.normalize();
		auto bullet = Bullet::create("bullet");
		bullet->setPosition(characterPos);
		float bulletSpeed = 200.0f;
		direction *= bulletSpeed;
		bullet->getPhysicsBody()->setVelocity(direction);
		bullet->setOwner(character);
		this->addChild(bullet, 1);

		return true;
	}

	return false;
}
bool GameScene::checkWinCondition()
{
	if (!Ended)
	{
		if (initialCountdownTime > 0)
		{
			elapsedTime += Director::getInstance()->getDeltaTime();
			int remainingTime = static_cast<int>(initialCountdownTime - elapsedTime);
			remainingTime = std::max(remainingTime, 0);
			timeLabel->setString(StringUtils::format("Time: %d", remainingTime));

			if (elapsedTime >= initialCountdownTime)
			{
				CCLOG("You lose!");
				this->removeChild(character, true);
				character = nullptr;
				Director::getInstance()->replaceScene(GameOverScene::createScene());
				return true;
			}
		}
		Vec2 characterTilePos = _gameMap->convertPosTileMap(character->getPosition());
		if (_gameMap->getMetaAtPos(characterTilePos) == GameMap::MetaGreen)
		{
			CCLOG("You win");
			this->removeChild(character, true);
			character = nullptr;
			auto gamewinScene = GameWinScene::create();
			Director::getInstance()->replaceScene(gamewinScene);
			Ended = true;
			return true;
		}

		return false;
	}

	return false;
}
void GameScene::onExit()
{
	AudioEngine::stop(bGM);
	Scene::onExit();
};

