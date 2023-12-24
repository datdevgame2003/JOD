#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "Menu.h"
#include "KeyboardInput.h"
#include "Map/GameMap.h"
#include "Character/Character.h"
#include "Camera/CameraFollow.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
Scene* GameScene::createScene()
{
	return GameScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

bool GameScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//AudioEngine::play2d("Audio/BGM.mp3", false, 1.0f);
	layer = Layer::create();

	EntityStat* characterStat = new EntityStat();
	characterStat->_runSpeed = 200.0f;

	character = Character::create(new EntityInfo(1, "Boy"));
	character->setEntityStat(characterStat);

	auto background = Sprite::create("bg1.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(2.5f);
	this->addChild(background);

	_gameMap = GameMap::create("/Map/map1.tmx");
	_gameMap->setTag(99);

	TMXObjectGroup* objGroup = _gameMap->getObjectGroup("SpawnPoint");
	ValueMap charPoint = objGroup->getObject("Hero");

	Vec2 position;
	position.x = charPoint["x"].asFloat();
	position.y = charPoint["y"].asFloat();

	character->setPosition(position);
	KeyboardInput::getInstance()->addKey(EventKeyboard::KeyCode::KEY_SPACE);
	this->addChild(_gameMap);
	this->addChild(layer, 100);
	this->addChild(character, 1);

	this->scheduleUpdate();

	auto button = ui::Button::create("14.png");
	button->setTitleText("Back");
	button->setTitleFontName("fonts/victoria.ttf");
	button->setTitleFontSize(100);
	button->setTitleColor(Color3B::BLACK);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				CCLOG("Button 1 clicked!");
				Director::getInstance()->replaceScene(TransitionFade::create(2, MenuScene::createScene()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}
		});
	button->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
	button->setScale(0.5);
	layer->addChild(button);

	this->scheduleUpdate();
	return true;
}
void GameScene::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	layer->setPosition(this->getDefaultCamera()->getPosition() + visibleSize / -2);
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
