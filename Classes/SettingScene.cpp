#include "SettingScene.h"
#include "Menu.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* Setting::createScene()
{
    return Setting::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Setting::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
    button->setPosition(Vec2(visibleSize.width / 2 - 550, visibleSize.height / 2 + 350));
    button->setScale(0.5);
    this->addChild(button);
    auto background = Sprite::create("setting_bg.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(3);
    this->addChild(background, -1);

    auto setting = Label::createWithSystemFont("Settings", "victoria.ttf", 50);
    setting->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 300));
    this->addChild(setting);
    auto bgMusic = Label::createWithSystemFont("Music", "victoria.ttf", 36);
    bgMusic->setPosition(Vec2(visibleSize.width / 2 - 250, visibleSize.height / 2 + 50));
    this->addChild(bgMusic);




    auto slider = ui::Slider::create();
    slider->loadBarTexture("loadingBar.png");
    slider->loadSlidBallTextures("kt.png");
    slider->loadProgressBarTexture("ldb.png");
    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    this->addChild(slider);
    //AudioEngine::play2d("BGM.mp3", true, 2.0f);
    slider->addEventListener([=](Ref* sender, ui::Slider::EventType tyle) {
        auto slider = dynamic_cast<ui::Slider*>(sender);
    if (tyle == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        CCLOG("%d", slider->getPercent());
    }
        });
    slider->setPercent(50);
    auto sfx = Label::createWithSystemFont("SFX", "Arial", 36);
    sfx->setPosition(Vec2(visibleSize.width / 2 - 250, visibleSize.height / 2 - 50));
    this->addChild(sfx);

    auto slider1 = ui::Slider::create();
    slider1->loadBarTexture("loadingBar.png");
    slider1->loadSlidBallTextures("kt.png");
    slider1->loadProgressBarTexture("ldb.png");
    slider1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
    slider1->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
    this->addChild(slider1);
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slidermusic = dynamic_cast<ui::Slider*>(sender);
        log("music percent: %d", slider->getPercent());
    }
        });
   
    return true;
}


void Setting::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}