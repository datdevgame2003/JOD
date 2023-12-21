#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"

class Tutorial : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    //bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Tutorial);
};

#endif // __TUTORIAL_SCENE_H__