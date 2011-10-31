//
//  EntityManager.cpp
//  angry_bus
//
//  Created by suning on 11-10-30.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "EntityManager.h"
#include "Entity.h"
EntityManager::EntityManager()
{
    
}

EntityManager::~EntityManager()
{
    NameEntityMap::iterator it = _entities.begin();
    for (; it != _entities.end(); ++it)
    {
        Entity* e = it->second;
        if (e)
        {
            delete e;
            e = 0;
        }
    }
    //
    _entities.clear();
}

Entity* EntityManager::createEntity(std::string const &name)
{
    NameEntityMap::iterator it = _entities.find(name);
    if (it == _entities.end())
    {
        _entities[name] = new Entity;
        _entities[name]->create();
    }
    
    return _entities[name];
}

Entity* EntityManager::createEntity(const char *name)
{
    return createEntity(std::string(name));
}