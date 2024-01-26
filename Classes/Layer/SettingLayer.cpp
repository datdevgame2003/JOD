#include "SettingLayer.h"
#include "GameScene.h"
#include "Menu.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraFollow.h"
#include "Map/GameMap.h"
USING_NS_CC;



bool SettingLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	scene = Scene::create();
	this->addChild(scene, 100);
	background = Sprite::create("bgs.png");

	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(visibleSize.height / background->getContentSize().height * 0.55);
	scene->addChild(background, 101);
	
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
	scene->addChild(buttonresume, 101);

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
	buttonQuit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4)); //0.4
	buttonQuit->setScale(visibleSize.height / buttonQuit->getContentSize().height * 0.15);
	scene->addChild(buttonQuit, 101);
	this->scheduleUpdate();
	return true;
}
void SettingLayer::update(float dt)
{
	//Director::getInstance()->getRunningScene();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	background->setPosition(getScene()->getDefaultCamera()->getPosition() + visibleSize / -2);
}