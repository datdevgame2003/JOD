#include "SplashScene.h"
#include "Menu.h"
#include "StartGame.h"
//#include "GameScene.h"
USING_NS_CC;

Scene* SplashScene::createScene()
{
	return SplashScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SplashScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("HelloWorld.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(1.0f);
	this->addChild(background);

	auto label = Label::createWithTTF("Journey Of Discovery", "fonts/victoria.ttf", 40);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	label->enableOutline(Color4B::GREEN, 1);
	label->enableGlow(Color4B::YELLOW);
	this->addChild(label);


	auto moveBy = MoveBy::create(1.5, Vec2(0, -200));
	auto callFunc = CallFunc::create([&]() {
		auto startScene = StartGame::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, startScene));
		});
	auto sequence = Sequence::create(moveBy, callFunc, nullptr);
	label->runAction(sequence);

}