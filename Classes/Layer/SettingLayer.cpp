#include "SettingLayer.h"
#include "GameScene.h"
#include "Menu.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
//
//Scene* SettingLayer::createScene()
//{
//	return SettingLayer::create();
//}

bool SettingLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("optionbox.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(visibleSize.height / background->getContentSize().height * 0.8);
	//background->setScale(4);
	this->addChild(background);

	auto buttonresume = ui::Button::create("resume.png");
	buttonresume->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				Director::getInstance()->resume();
				this->removeFromParentAndCleanup(true);
				break; }
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonresume->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.65));
	buttonresume->setScale(visibleSize.height / buttonresume->getContentSize().height * 0.15);
	this->addChild(buttonresume, 5);

	
	auto buttonRestart = ui::Button::create("restart.png");
	buttonRestart->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->resume();
				Director::getInstance()->replaceScene(GameScene::create());
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonRestart->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.45));
	buttonRestart->setScale(visibleSize.height / buttonRestart->getContentSize().height * 0.15);
	this->addChild(buttonRestart, 5);
	

	auto buttonQuit = ui::Button::create("home.png");
	buttonQuit->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->resume();
				this->removeFromParentAndCleanup(true);
				Director::getInstance()->replaceScene(MenuScene::createScene());
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonQuit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
	buttonQuit->setScale(visibleSize.height / buttonQuit->getContentSize().height * 0.15);
	this->addChild(buttonQuit, 5);

	//Director::getInstance()->getActionManager()->pauseAllRunningActions();
	return true;
}
