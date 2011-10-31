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
class Entity;
class EntityManager : public Singleton<EntityManager>
{
public:
    EntityManager();
    ~EntityManager();
  
    Entity* createEntity(const std::string& name);
    Entity* createEntity(const char* name);
private:
    typedef std::map<std::string, Entity*> NameEntityMap;
    NameEntityMap   _entities;
};

#endif