#ifndef __KEYBOARD_INPUT_H__
#define __KEYBOARD_INPUT_H__

#include "cocos2d.h"

USING_NS_CC;

class KeyboardInput : public Node
{
public:
	static KeyboardInput* getInstance();
	Vec2 getDirection();
	void addKey(EventKeyboard::KeyCode key);
	bool getKey(EventKeyboard::KeyCode key);
	void removeKey(EventKeyboard::KeyCode key);
	void onKeyPressed(EventKeyboard::KeyCode key, Event* ev);
	void onKeyReleased(EventKeyboard::KeyCode key, Event* ev);
private:
	bool init() override;
private:
	static KeyboardInput* _instance;
	std::map<EventKeyboard::KeyCode, bool> _keys;
	float _horizontal, _vertical;


};

#endif // !__KEYBOARD_INPUT_H__