#ifndef __STARTGAME_H__
#define __STARTGAME_H__

#include "cocos2d.h"

class StartGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartGame);
};

#endif // __STARTGAME_H__