#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "Menu.h"
#include "KeyboardInput.h"
#include "Map/GameMap.h"
#include "Character/Character.h"
#include "Camera/CameraFollow.h"
#include "audio/include/AudioEngine.h"
#include "Layer/SettingLayer.h"
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
	auto winSize = Director::getInstance()->getWinSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	elapsedTime = 0.0f;
	Ended = false;

	
	timeLabel = Label::createWithTTF("Time: ", "fonts/Marker Felt.ttf", 30);
	timeLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
	timeLabel->enableGlow(Color4B::RED);
	timeLabel->enableOutline(Color4B::RED, 1);
	this->addChild(timeLabel, 100);


	layer = Layer::create();

	EntityStat* characterStat = new EntityStat();
	characterStat->_runSpeed = 200.0f;

	character = Character::create(new EntityInfo(1, "Boy"));
	character->setEntityStat(characterStat);


	_gameMap = GameMap::create("Map/map1.tmx");
	_gameMap->setTag(99);
	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("Nv");


	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	character->setPosition(position);
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);
	this->addChild(_gameMap);
	this->addChild(layer, 100);
	this->addChild(character, 1);
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
				auto layer1 = SettingLayer::create();
				this->addChild(layer1, 101);
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonSetting->setPosition(Vec2(visibleSize.width / 20, visibleSize.height * 0.9));
	buttonSetting->setScale(visibleSize.height / buttonSetting->getContentSize().height * 0.1);
	layer->addChild(buttonSetting, 99);

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
	//auto button = ui::Button::create("Time.png");
	/*button->setPosition(Vec2(visibleSize.width / 2.5, visibleSize.height / 1.5));
	this->addChild(button);*/
	
	
	elapsedTime += 1.0f;
	int remainingTime = static_cast<int>(120.0f - elapsedTime);
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

