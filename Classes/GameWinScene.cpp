#include "GameWinScene.h"
#include "Menu.h"
#include "Map/GameMap.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;

bool GameWinScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//AudioEngine::play2d("Audio/yeah.mp3", false, 1.0f);
	auto background = Sprite::create("gamewin.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(2.0f);
	this->addChild(background);

	/*auto label = Label::createWithTTF("Win", "fonts/Marker Felt.ttf", 40);
	label->setTextColor(Color4B::BLUE);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(label);*/

	auto buttonExit = ui::Button::create("ui5.png", "ui5.png");
	buttonExit->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
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

	/*auto buttonagain = ui::Button::create("again.png", "again.png");
	buttonagain->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonagain->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
	this->addChild(buttonagain);*/
	/*auto playAgainButton = MenuItemImage::create(
		"again.png",
		"again.png",
		CC_CALLBACK_1(GameWinScene::playAgainCallback, this));

	playAgainButton->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));

	auto menu = Menu::create(playAgainButton, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);*/

	return true;
}

//void GameWinScene::playAgainCallback(cocos2d::Ref* pSender)
//{
//	auto gameScene = GameScene::create(mapName);
//	Director::getInstance()->replaceScene(gameScene);
//}


