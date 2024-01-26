#include "SettingScene.h"
#include "Menu.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
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

    auto buttonQuit = ui::Button::create("home.png");
    buttonQuit->addTouchEventListener(
        [&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                Director::getInstance()->replaceScene(MenuScene::createScene());
                break;
            case ui::Widget::TouchEventType::CANCELED:
                break;
            default:
                break;
            }});
    buttonQuit->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.9));
    buttonQuit->setScale(2);
    this->addChild(buttonQuit);

    auto background = Sprite::create("setting_bg.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(3);
    this->addChild(background, -1);

    auto setting = Label::createWithSystemFont("SETTINGS", "fonts/victoria.ttf", 65);
    setting->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 300));
    this->addChild(setting);
    auto bgMusic = Label::createWithSystemFont("MUSIC", "fonts/victoria.ttf", 36);
    bgMusic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2 + 50));
    this->addChild(bgMusic);

    //music
    int id1 = AudioEngine::play2d("Audio/BGM.mp3", true, 1.0f);
    auto slider = ui::Slider::create();
    slider->loadBarTexture("loadingBar.png");
    slider->loadSlidBallTextures("kt.png");
    slider->loadProgressBarTexture("ldb.png");
    slider->setPercent(100);
    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    this->addChild(slider);
    slider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {

        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto slider = dynamic_cast<ui::Slider*>(sender);
            log("music percent: %d", id1);
            AudioEngine::setVolume(id1, (float)slider->getPercent() / 100);
        }
        });



    auto sfx = Label::createWithSystemFont("SFX", "Arial", 36);
    sfx->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height / 2 - 100));
    this->addChild(sfx);

    //sfx
    int id = AudioEngine::play2d("Audio/attack.mp3", true, 1.0f);
    auto slider1 = ui::Slider::create();
    slider1->loadBarTexture("loadingBar.png");
    slider1->loadSlidBallTextures("kt.png");
    slider1->loadProgressBarTexture("ldb.png");
    slider1->setPercent(100);
    slider1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
    this->addChild(slider1);

    slider1->addEventListener([=](Ref* sender, ui::Slider::EventType type) {

        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto slidermusic = dynamic_cast<ui::Slider*>(sender);
            log("sfx percent: %d", id);
            AudioEngine::setVolume(id, (float)slidermusic->getPercent() / 100);
        }





















        
        });

    return true;
}


void Setting::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}