#include "Event.h"
EventManager::EventManager()
{
    
}
EventManager::~EventManager()
{
    
}
void EventManager::fireEvent(sEvent *e)
{
    if (e)
    {
        EventEventHandlerMap::iterator it = _events.find(e->eventID);
        if (it == _events.end())
        {
            return;
        }
        IEventHandlerVector v = it->second;
        for (size_t i = 0; i != v.size(); ++i)
        {
            v[i]->onEvent(e);
        }
    }
}
void EventManager::subscribeEvent(eEvent eventID, IEventHandler *handler)
{
    if (handler)
    {
        EventEventHandlerMap::iterator it = _events.find(eventID);
        if (it == _events.end())
        {
            IEventHandlerVector v;
            v.push_back(handler);
            _events[eventID] = v;
        }
        else
        {
            IEventHandlerVector v = it->second;
            v.push_back(handler);
        }
    }
}
void EventManager::unsubscribeEvent(eEvent eventID, IEventHandler *handler)
{
    if (handler)
    {
        EventEventHandlerMap::iterator it = _events.find(eventID);
        if (it == _events.end())
        {
            return;
        }
        else
        {
            IEventHandlerVector v = it->second;
            for (IEventHandlerVector::iterator i = v.begin(); i != v.end(); ++i)
            {
                if (*i == handler)
                {
                    v.erase(i);
                    break;
                }
            }
        }
    }
}