#ifndef  __GAME_SCENE_H__
#define  __GAME_SCENE_H__
#include "cocos2d.h"
#include "GameScene.h"
#include "Character/Character.h"
#include "Map/GameMap.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    //static const int idAudio;
protected:
    Layer* layer;
    Character* character;
    GameMap* _gameMap;
   /* float elapsedTime;
    bool Ended;
    Label* timeLabel;*/
protected:
    //void resetGame();
    void update(float dt) override;
    void onEnter() override;
   /* bool checkWinCondition();
    void updateTime(float dt);*/
};
#endif // __GAME_SCENE_H__