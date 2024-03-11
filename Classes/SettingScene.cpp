#include "SettingScene.h"
#include "Menu.h"
#include"ui/CocosGUI.h"
#include"AudioEngine.h"
USING_NS_CC;
ui::Slider* slider;
ui::Slider* slider1;
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
    auto background = Sprite::create("setting_bg.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    background->setScale(3);
    this->addChild(background, -1);


    auto button = ui::Button::create("back.png");
    button->setTitleText("Back");
    button->setTitleFontName("fonts/victoria.ttf");
    button->setTitleFontSize(40);
    button->setTitleColor(Color3B::BLACK);
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                clickAudio = AudioEngine::play2d("Audio/click.mp3");
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
    button->setScale(1.5);
    this->addChild(button);

    auto setting = Label::createWithSystemFont("Settings", "victoria.ttf", 50);
    setting->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 300));
    this->addChild(setting);
    auto bgMusic = Label::createWithSystemFont("BG Music", "victoria.ttf", 36);
    bgMusic->setPosition(Vec2(visibleSize.width / 2 - 250, visibleSize.height / 2 + 50));
    this->addChild(bgMusic);

    //int id = AudioEngine::play2d("Audio/BGM.mp3", true, 1.0f);
    slider = ui::Slider::create();
    slider->loadBarTexture("loadingBar.png");
    slider->loadSlidBallTextures("kt.png");
    slider->loadProgressBarTexture("ldb.png");
    //slider->setPercent(100);
    slider->setPercent(UserDefault::getInstance()->getFloatForKey("bgMusicVolume", 100.0f));
    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
    slider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {

        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto slidermusic = dynamic_cast<ui::Slider*>(sender);
            log("music percent: %d", bGM, soundWin, soundLose);
            AudioEngine::setVolume(bGM, (float)slidermusic->getPercent() / 100);
            AudioEngine::setVolume(soundWin, (float)slidermusic->getPercent() / 100);
            AudioEngine::setVolume(soundLose, (float)slidermusic->getPercent() / 100);
        }
        });

    this->addChild(slider);


    auto sfx = Label::createWithSystemFont("SFX", "Arial", 36);
    sfx->setPosition(Vec2(visibleSize.width / 2 - 250, visibleSize.height / 2 - 50));
    this->addChild(sfx);
    //int id1 = AudioEngine::play2d("Audio/attack.mp3", false, 1.0f);
    auto slider1 = ui::Slider::create();
    slider1->loadBarTexture("loadingBar.png");
    slider1->loadSlidBallTextures("kt.png");
    slider1->loadProgressBarTexture("ldb.png");
    slider1->setPercent(UserDefault::getInstance()->getFloatForKey("sfxVolume", 100.0f));
    slider1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
    slider1->addEventListener([=](Ref* sender, ui::Slider::EventType type) {

        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto slidermusic1 = dynamic_cast<ui::Slider*>(sender);
            log("music percent: %d", soundAttack, soundDead, clickAudio);
            AudioEngine::setVolume(soundAttack, (float)slidermusic1->getPercent() / 100);
            AudioEngine::setVolume(soundDead, (float)slidermusic1->getPercent() / 100);
            AudioEngine::setVolume(clickAudio, (float)slidermusic1->getPercent() / 100);
        }
        });
    this->addChild(slider1);
    return true;
}
void Setting::onEnter()
{
    Scene::onEnter();

}

void Setting::onExit()
{
    UserDefault::getInstance()->setFloatForKey("bgMusicVolume", slider->getPercent());
    UserDefault::getInstance()->flush();
    //UserDefault::getInstance()->setFloatForKey("sfxVolume", slider1->getPercent(slider1));
    //UserDefault::getInstance()->flush();

    Scene::onExit();
}