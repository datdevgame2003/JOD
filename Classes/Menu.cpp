#include "Menu.h"
//#include "GameScene.h"
#include "SettingScene.h"
#include "ui/CocosGUI.h"
#include "TutorialScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MenuScene::init() {
	if (!Scene::init())
	{
		return false;
	}
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto nameGame = Label::createWithTTF("Journey Of Discovery", "fonts/victoria.ttf", 150);
    nameGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 250));
    nameGame->enableGlow(Color4B::GREEN);
    this->addChild(nameGame);

    auto background = Sprite::create("mainmenu.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, -1);

    auto button = ui::Button::create("14.png");
    button->setTitleText("Play");
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
                //Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene()));
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
    button->setScale(0.5);
    this->addChild(button);

    auto button1 = ui::Button::create("14.png");
    button1->setTitleText("Setting");
    button1->setTitleFontName("fonts/victoria.ttf");
    button1->setTitleFontSize(100);
    button1->setTitleColor(Color3B::BLACK);
    button1->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("Button 1 clicked!");
                Director::getInstance()->replaceScene(TransitionFade::create(2, Setting::createScene()));
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    button1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.0));
    button1->setScale(0.5);
    this->addChild(button1);

    auto button2 = ui::Button::create("14.png");
    button2->setTitleText("Tutorial");
    button2->setTitleFontName("fonts/victoria.ttf");
    button2->setTitleFontSize(100);
    button2->setTitleColor(Color3B::BLACK);
    button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("Button 1 clicked!");
                Director::getInstance()->replaceScene(TransitionFade::create(2, Tutorial::createScene()));
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    button2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.9));
    button2->setScale(0.5);
    this->addChild(button2);

    auto button3 = ui::Button::create("14.png");
    button3->setTitleText("Quit");
    button3->setTitleFontName("fonts/victoria.ttf");
    button3->setTitleFontSize(100);
    button3->setTitleColor(Color3B::BLACK);
    button3->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("Button 3 clicked!");
                Director::getInstance()->end();
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }
        });
    button3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5.3));
    button3->setScale(0.5);
    this->addChild(button3);


    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}