#include "GameOverScene.h"
#include "Menu.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto newObject = new GameOverScene();
	if (newObject != nullptr && newObject->init())
	{
		newObject->autorelease();
		return newObject;
	}

	CC_SAFE_DELETE(newObject);
	return nullptr;
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOverScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//AudioEngine::play2d("Audio/oversad.mp3", false, 1.0f);
	auto background = Sprite::create("gameover.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(2.0f);
	this->addChild(background);

	auto buttonExit = ui::Button::create("ui5.png", "ui5.png");
	buttonExit->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(2, MenuScene::createScene()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.2));
	this->addChild(buttonExit);

	/*auto buttonagain = ui::Button::create("restart.png", "restart.png");
	buttonagain->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:

				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create("map1")));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonagain->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
	this->addChild(buttonagain);*/
	//auto buttonagain = ui::Button::create("restart.png", "restart.png");
	//buttonagain->addTouchEventListener(
	//	[&](Ref* sender, ui::Widget::TouchEventType type) {
	//		switch (type)
	//		{
	//		case ui::Widget::TouchEventType::BEGAN:
	//			break;
	//		case ui::Widget::TouchEventType::ENDED:
	//		{
	//			std::string mapName = "map1";
	//			std::string mapName1 = "map2";
	//			std::string mapName2 = "map3";
	//			std::string mapName3 = "map4";
	//			// Kiểm tra nếu mapName là "map2", "map3", hoặc "map4" thì sẽ gán mapName tương ứng
	//				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create(mapName)));
	//			
	//			
	//				mapName1 = "map2";
	//				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create(mapName1)));
	//			
	//			
	//				mapName2 = "map3";
	//				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create(mapName2)));
	//			
	//			
	//				mapName3 = "map4";
	//				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create(mapName3)));
	//			
	//			// Thực hiện replacescene dựa trên mapName đã được gán
	//			//Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::create(mapName)));
	//		}
	//		break;
	//		case ui::Widget::TouchEventType::CANCELED:
	//			break;
	//		default:
	//			break;
	//		}
	//	});
	//buttonagain->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
	//this->addChild(buttonagain);

	return true;
}
