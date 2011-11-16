#ifndef _ButtonCallbackManager_
#define _ButtonCallbackManager_
#include "Singleton.h"
#include <string>
#include <map>
class IButtonPushedCallBack;
class ButtonCallbackManager: public Singleton<ButtonCallbackManager>
{
public:
    ButtonCallbackManager();
    ~ButtonCallbackManager();

    void initCallbacks();
    IButtonPushedCallBack* getCallback(const std::string& name);
private:
    typedef std::map<std::string, IButtonPushedCallBack*> NameCallbackMap;
    NameCallbackMap _callbacks;
};
#endif
