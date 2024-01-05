#include "Level.h"
#include "ui/CocosGUI.h"
//#include "json/rapidjson.h"
//#include "json/document.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

#include "Entity/EntityDAL.h"

bool Level::init()
{
	if (!Scene::init())
	{
		log("Init Level failed!");
		return false;
	}

	std::vector<std::string> maps;
	maps.push_back("map1");
	maps.push_back("map2");
	maps.push_back("map3");

	float x = Director::getInstance()->getVisibleSize().width / 2;

	for (int i = 0; i < maps.size(); ++i)
	{
		auto button = ui::Button::create("BtnBlue.png");
		button->setTitleText("Level " + std::to_string(i + 1));
		button->setScale(2);
		button->setTitleFontSize(button->getTitleFontSize() * 2);
		button->setPositionX(200 + 200 * i);
		button->setPositionY(450);

		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					auto gameScene = GameScene::create(maps[i]);
					Director::getInstance()->replaceScene(gameScene);
				}
			});

		this->addChild(button, 1);
	}

	return true;
}
