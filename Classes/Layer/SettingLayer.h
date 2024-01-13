#ifndef  __SETTING_LAYER_H__
#define  __SETTING_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class SettingLayer : public cocos2d::Layer {
public:

	virtual bool init();
	CREATE_FUNC(SettingLayer);
protected:
	Sprite* background;
protected:
	Scene* scene;
protected:
	void update(float dt);
};

#endif // __SETTING_LAYER_H__
