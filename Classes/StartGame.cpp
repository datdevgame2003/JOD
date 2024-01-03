#include "StartGame.h"
#include "Menu.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* StartGame::createScene()
{
    return StartGame::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StartGame::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("br.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, -1);

    auto nameGame = Label::createWithTTF("Journey Of Discovery", "fonts/victoria.ttf", 150);
    nameGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 490));
    nameGame->enableGlow(Color4B::GREEN);
    this->addChild(nameGame);

    auto button = ui::Button::create("BtnBlue.png");
    button->setTitleText("Start");
    button->setTitleFontName("fonts/victoria.ttf");
    button->setTitleFontSize(140);
    button->setTitleColor(Color3B::ORANGE);
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
    button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300));
    button->setScale(0.3);
    this->addChild(button);

    return true;
}


void StartGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
