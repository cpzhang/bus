#include "ButtonCallbackManager.h"
ButtonCallbackManager::ButtonCallbackManager()
{
}

ButtonCallbackManager::~ButtonCallbackManager()
{
    for(NameCallbackMap::iterator it = _callbacks.begin(); it != _callbacks.end(); ++it)
    {
	IButtonPushedCallBack* cb = it->second;
	delete cb;
    }
    _callbacks.clear();
}

void ButtonCallbackManager::initCallbacks()
{
    _callbacks["go to playing state"] = new ButtonPushedCallBack_Enter;
    _callbacks["go to about us state"] = new ButtonPushedCallBack_Us;
    _callbacks["go to entry point state"] = new ButtonPushedCallBack_GotoEntryPoint;
    _callbacks["setting button in entry point state"] = new ButtonPushedCallBack_Setting;
    _callbacks["sound button in entry point state"] = new ButtonPushedCallBack_Sound;
}

IButtonPushedCallBack* ButtonCallbackManager::getCallback(const std::string& name)
{
    NameCallbackMap::iterator it = _callbacks.find(name);
    if(it == _callbacks.end())
    {
	return 0;
    }
    return it->second;
}
