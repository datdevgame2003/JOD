#include "TutorialScene.h"
#include "Menu.h"
#include "ui/CocosGUI.h"
#include "ui/UIRichText.h"
#include"AudioEngine.h"
USING_NS_CC;

Scene* Tutorial::createScene()
{
	return Tutorial::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Tutorial::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int clickAudio;
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
	ui::RichText* richtext = ui::RichText::create();
	richtext->ignoreContentAdaptWithSize(false);
	richtext->setContentSize(Size(1000, 800));
	richtext->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + 200 - origin.y));

	ui::RichElementText* hello = ui::RichElementText::create(1, Color3B::BLACK, 255, "Welcome to Journey of Discovery!", "victoria.ttf", 30);
	ui::RichElementText* hello1 = ui::RichElementText::create(1, Color3B::BLACK, 255, "\nYou will participate in an exciting journey in a maze full of mysteries and challenges. Get ready to explore and tackle monsters to reach the final goal.", "victoria.ttf", 24);
	ui::RichElementText* hello2 = ui::RichElementText::create(1, Color3B::BLACK, 255, "\n\nGameplay Guide:", "victoria.ttf", 30);

	richtext->pushBackElement(hello);
	richtext->pushBackElement(hello1);
	richtext->pushBackElement(hello2);

	ui::RichText* richtext1 = ui::RichText::create();
	richtext1->ignoreContentAdaptWithSize(false);
	richtext1->setContentSize(Size(1000, 800));
	richtext1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


	ui::RichElementText* moveC1 = ui::RichElementText::create(1, Color3B::BLACK, 255, "- Use navigation keys", "victoria.ttf", 24);
	ui::RichElementImage* ima1 = ui::RichElementImage::create(2, Color3B::WHITE, 255, "w.png");
	ui::RichElementImage* ima2 = ui::RichElementImage::create(3, Color3B::WHITE, 255, "s.png");
	ui::RichElementImage* ima3 = ui::RichElementImage::create(4, Color3B::WHITE, 255, "a.png");
	ui::RichElementImage* ima4 = ui::RichElementImage::create(5, Color3B::WHITE, 255, "d.png");
	ui::RichElementText* moveC2 = ui::RichElementText::create(6, Color3B::BLACK, 255, "to move your character up, down, left, and right.", "victoria.ttf", 24);
	ui::RichElementText* avoid = ui::RichElementText::create(7, Color3B::BLACK, 255, "\n- You have to overcome obstacles like walls and fight monsters ", "victoria.ttf", 24);
	ui::RichElementImage* quai = ui::RichElementImage::create(8, Color3B::WHITE, 255, "quai.png");
	ui::RichElementText* avoid1 = ui::RichElementText::create(9, Color3B::BLACK, 255, " to find the right path.", "victoria.ttf", 24);
	ui::RichElementText* avoid2 = ui::RichElementText::create(10, Color3B::BLACK, 255, "\n- The game has four difficulty levels easy, medium, hard, and extremely difficult, corresponding to four maps", "victoria.ttf", 24);
	ui::RichElementText* avoid3 = ui::RichElementText::create(11, Color3B::BLACK, 255, ".You have to face increasing danger as you progress through each map with more powerful monsters.", "victoria.ttf", 24);
	ui::RichElementText* lv = ui::RichElementText::create(12, Color3B::BLACK, 255, "\nEach level presents unique challenges. Solve the maze and reach the destination to unlock new levels.", "victoria.ttf", 24);
	ui::RichElementText* gb = ui::RichElementText::create(13, Color3B::BLACK, 255, "\n\nWish you an exciting journey and success in Journey of Discovery!", "victoria.ttf", 24);

	richtext1->pushBackElement(moveC1);
	richtext1->pushBackElement(ima1);
	richtext1->pushBackElement(ima2);
	richtext1->pushBackElement(ima3);
	richtext1->pushBackElement(ima4);
	richtext1->pushBackElement(moveC2);
	richtext1->pushBackElement(avoid);
	richtext1->pushBackElement(quai);
	richtext1->pushBackElement(avoid1);
	richtext1->pushBackElement(avoid2);
	richtext1->pushBackElement(avoid3);
	richtext1->pushBackElement(lv);
	richtext1->pushBackElement(gb);

	this->addChild(richtext);
	this->addChild(richtext1);

	return true;
}


void Tutorial::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}