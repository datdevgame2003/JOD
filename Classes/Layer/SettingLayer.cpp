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
	
    background = Sprite::create("ob.png");
	
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(visibleSize.height / background->getContentSize().height * 0.75);
	//background->setScale(1);
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
	this->addChild(buttonresume, 105);

	std::vector<std::string> maps;
	maps.push_back("map1");
	maps.push_back("map2");
	maps.push_back("map3");

	for (int i = 0; i < maps.size(); ++i)
	{
		auto buttonRestart = ui::Button::create("restart.png");
		buttonRestart->addTouchEventListener(
			[&maps, i](Ref* sender, ui::Widget::TouchEventType type) {
				switch (type)
				{
				case ui::Widget::TouchEventType::BEGAN:
					break;
				case ui::Widget::TouchEventType::ENDED:
					Director::getInstance()->resume();

					Director::getInstance()->replaceScene(GameScene::create(maps[i]));

					break;
				case ui::Widget::TouchEventType::CANCELED:
					break;
				default:
					break;
				}
			});
		buttonRestart->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.45));
		buttonRestart->setScale(visibleSize.height / buttonRestart->getContentSize().height * 0.15);
		this->addChild(buttonRestart, 5);

	}
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
	//this->scheduleUpdate();
	return true;
}
void SettingLayer::update(float dt)
{
	/*auto background = Director::getInstance()->getRunningScene();*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*auto runningScene = Director::getInstance()->getRunningScene();
	if (runningScene) {*/
		background->setPosition(getScene()->getDefaultCamera()->getPosition() + visibleSize / -2.5);
		
	
}
