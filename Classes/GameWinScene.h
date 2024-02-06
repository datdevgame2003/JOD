#ifndef  __GAMEWIN_SCENE_H__
#define  __GAMEWIN_SCENE_H__

#include "cocos2d.h"

class GameWinScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void playAgainCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameWinScene);

};
#endif // __GAMEWIN_SCENE_H__