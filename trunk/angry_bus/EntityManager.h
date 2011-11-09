//
//  EntityManager.h
//  angry_bus
//
//  Created by suning on 11-10-30.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _EntityManager_
#define _EntityManager_

#include <map>
#include <string>
#include "Singleton.h"
#include "b2WorldCallbacks.h"

class Entity;

class EntityManager : public b2ContactListener, public b2QueryCallback, public Singleton<EntityManager>
{
public:
    EntityManager();
    ~EntityManager();
  
    Entity* createEntity(const std::string& name);
    Entity* getEntity(const std::string& name);
    
    /// Called when two fixtures begin to touch.
	virtual void BeginContact(b2Contact* contact);
    
	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact);
    
	virtual bool ReportFixture(b2Fixture* fixture);

	void createUI();
private:
    typedef std::map<std::string, Entity*> NameEntityMap;
    NameEntityMap   _entities;
};

#endif
