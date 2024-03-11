#include "json/document.h"
#include "json/rapidjson.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "Level.h"
#include "Menu.h"
#include "Entity/EntityDAL.h"
#include"AudioEngine.h"
bool Level::init()
{
	if (!Scene::init())
	{
		log("Init Test failed!");
		return false;
	}

	std::vector<std::string> maps;
	maps.push_back("map1");
	maps.push_back("map2");
	maps.push_back("map3");
	maps.push_back("map4");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float gapBetweenButtons = 350;
	auto background = Sprite::create("setting_bg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(3);
	this->addChild(background, -1);
	auto button1 = ui::Button::create("back.png");
	button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				clickAudio = AudioEngine::play2d("Audio/click.mp3");
				break;
			case ui::Widget::TouchEventType::ENDED:
				CCLOG("Back clicked!");
				Director::getInstance()->replaceScene(TransitionFade::create(1, MenuScene::create()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}
		});
	button1->setPosition(Vec2(visibleSize.width / 2 - 550, visibleSize.height / 2 + 350));
	button1->setScale(0.5);
	this->addChild(button1);

	// tong chieu dai cua cac button va khoang cach giua chung
	float totalButtonsWidth = (maps.size() - 1) * gapBetweenButtons;

	float startX = (visibleSize.width - totalButtonsWidth) / 2; // dien bat dau giua cac button

	for (int i = 0; i < maps.size(); ++i)
	{
		auto button = ui::Button::create("door.png");
		button->setTitleText("World " + std::to_string(i + 1));
		button->setTitleFontSize(button->getTitleFontSize() * 1.5);
		float buttonX = startX + i * gapBetweenButtons;
		button->setPosition(Vec2(buttonX, visibleSize.height / 2));
		button->setScale(3);
		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					clickAudio = AudioEngine::play2d("Audio/click.mp3");
					auto gameScene = GameScene::create(maps[i]);
					Director::getInstance()->replaceScene(gameScene);
				}
			});

		this->addChild(button, 1);
	}

	return true;
}