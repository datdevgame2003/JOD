#ifndef  __GAME_SCENE_H__
#define  __GAME_SCENE_H__
#include "cocos2d.h"
#include "Character/Character.h"
#include "Map/GameMap.h"
#include "ui/CocosGUI.h"
//#include"Layer/SettingLayer.h"
USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
    static Scene* create(std::string mapName);

    virtual bool init(std::string mapName);
   
        //static const int idAudio;
protected:
    Layer* layer;
    Character* character;
    GameMap* _gameMap;
    float elapsedTime;
    int enemyLevelMap;
    Label* timeLabel;
    float initialCountdownTime;
    int bGM;
    int soundAttack;
    int clickAudio;
    bool Ended;
    

protected:
    void update(float dt) override;
    void onEnter() override;
    bool checkWinCondition();
    void onExit();
    bool onTouchBegan(Touch* touch, Event* event);
    void updateTime(float dt);
private:
    bool attackSoundPlayed;
    bool attackAnimationPlayed;
};

#endif // __GAME_SCENE_H__