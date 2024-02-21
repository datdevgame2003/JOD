#include "StateMachine.h"
#include "Map/GameMap.h"

StateMachine* StateMachine::create(Entity* owner)
{
    auto newObject = new StateMachine();
    if (newObject != nullptr && newObject->init(owner))
    {
        newObject->autorelease();
        return newObject;
    }

    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool StateMachine::init(Entity* owner)
{
    if (!Node::init())
    {
        log("Init StateMachine failed!");
        return false;
    }

    this->_owner = owner;
    this->scheduleUpdate();
    return true;
}

void StateMachine::addState(std::string stateName, State* newState)
{
    _states[stateName] = newState;
}

void StateMachine::setCurrentState(std::string stateName)
{
    _currentState = stateName;
}
std::string StateMachine::getState()
{
    return _currentState;
}

void StateMachine::update(float dt)
{
    std::string newState = _states[_currentState]->updateState();
    if (newState != _currentState)
    {
        _states[_currentState]->exitState();
        _currentState = newState;
        _states[_currentState]->enterState(_owner);
    }
}

void StateMachine::onEnter()
{
    Node::onEnter();
    _states[_currentState]->enterState(_owner);
}
