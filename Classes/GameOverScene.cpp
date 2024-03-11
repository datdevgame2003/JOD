#include "GameOverScene.h"
#include "Menu.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameOverScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int soundLose = AudioEngine::play2d("Audio/gameover.mp3", false, 1.0f);
	AudioEngine::setFinishCallback(soundLose, [=](int audioId, const std::string& filePath)
		{
			int soundLose = AudioEngine::play2d("Audio/gameover.mp3", false, 1.0f);
		});

	auto background = Sprite::create("gameover.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(2.0f);
	this->addChild(background);

	auto buttonExit = ui::Button::create("back.png");
	buttonExit->addTouchEventListener(
		[=](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				clickAudio = AudioEngine::play2d("Audio/click.mp3");
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(2, MenuScene::createScene()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.2));
	this->addChild(buttonExit);

	return true;
}
void GameOverScene::onExit()
{
	AudioEngine::stop(soundLose);
	Scene::onExit();
}