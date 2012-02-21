#include "ButtonCallbackManager.h"
#include "IComponent.h"
#include "ButtonComponent.h"
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
    _callbacks["go to playing state in glacier"] = new ButtonPushedCallBack_Enter<eState_Playing, eScene_Glacier>;
    _callbacks["go to playing state in city"] = new ButtonPushedCallBack_Enter<eState_Playing, eScene_City>;
    _callbacks["go to playing state in wetLand"] = new ButtonPushedCallBack_Enter<eState_Playing, eScene_WetLand>;
    _callbacks["go to about us state"] = new ButtonPushedCallBack_Enter<eState_AboutUs>;
    _callbacks["go to entry point state"] = new ButtonPushedCallBack_Enter<eState_EntryPoint>;
    _callbacks["go to level selection state"] = new ButtonPushedCallBack_Enter<eState_LevelSelection>;
    _callbacks["setting button in entry point state"] = new ButtonPushedCallBack_Setting;
    _callbacks["sound button in entry point state"] = new ButtonPushedCallBack_Sound;
    _callbacks["go to next level"] = new ButtonPushedCallStatePlaying_NextLevel;
    _callbacks["do the same level again"] = new ButtonPushedCallStatePlaying_DoTheSameLevelAgain;
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
