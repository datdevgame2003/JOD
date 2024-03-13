#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"

USING_NS_CC;

class Level : public Scene
{
public:
	bool init() override;
	//int count = 0;
	CREATE_FUNC(Level);
protected:
	int clickAudio;
};

#endif // !__LEVEL_H__
