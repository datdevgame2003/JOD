#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

class Setting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onEnter();
    void onExit();
    CREATE_FUNC(Setting);
protected:
    int bGM;
    int soundWin;
    int soundLose;
    int soundAttack;
    int soundDead;
    int clickAudio;
};

#endif // __SETTING_SCENE_H__
