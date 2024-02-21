#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "cocos2d.h"
#include "State.h"

USING_NS_CC;

class StateMachine : public Node
{
public:
	static const int AnimationTag = 1;
public:
	static StateMachine* create(Entity* owner);
	bool init(Entity* owner);

	void addState(std::string stateName, State* newState);
	void setCurrentState(std::string stateName);
	std::string getState();
protected:
	std::map<std::string, State*> _states;
	std::string _currentState;
	Entity* _owner;
protected:
	void update(float dt) override;
	void onEnter() override;
};

#endif // !__STATE_MACHINE_H__