//
//  Event.h
//  angry_bus
//
//  Created by suning on 12-2-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef angry_bus_Event_h
#define angry_bus_Event_h
#include <string>
#include <map>
#include <vector>
#include "Singleton.h"
enum eEvent
{
    eEvent_Null = 0,
    eEvent_LevelFinished,
};
struct sEvent
{
    sEvent()
    :eventID(eEvent_Null)
    {
        
    }
    
    eEvent eventID;
};
struct IEventHandler
{
    virtual void onEvent(sEvent* e) = 0; 
};
class EventManager : public Singleton<EventManager>
{
public:
    EventManager();
    ~EventManager();
public:
    void fireEvent(sEvent* e);
    void subscribeEvent(eEvent eventID, IEventHandler* handler);
    void unsubscribeEvent(eEvent eventID, IEventHandler* handler);
private:
    typedef std::vector<IEventHandler*> IEventHandlerVector;
    typedef std::map<eEvent, IEventHandlerVector> EventEventHandlerMap;
    EventEventHandlerMap _events;
};
#endif
