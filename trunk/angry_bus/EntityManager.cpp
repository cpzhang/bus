//
//  EntityManager.cpp
//  angry_bus
//
//  Created by suning on 11-10-30.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "EntityManager.h"
#include "Entity.h"
#include "b2Contact.h"
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

Entity* EntityManager::getEntity(std::string const &name)
{
   NameEntityMap::iterator it = _entities.find(name);
    if (it == _entities.end())
    {
	return 0;
    }
    
    return _entities[name];
}

void EntityManager::BeginContact(b2Contact *contact)
{
    //check if fixture A was a ball
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
    {
        static_cast<Entity*>( bodyUserData )->startContact();
    }
    //check if fixture B was a ball
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Entity*>( bodyUserData )->startContact();
}

void EntityManager::EndContact(b2Contact *contact)
{
    //check if fixture A was a ball
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Entity*>( bodyUserData )->endContact();
    
    //check if fixture B was a ball
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<Entity*>( bodyUserData )->endContact();
}

bool EntityManager::ReportFixture(b2Fixture* fixture) 
{
    return true;//keep going to find all fixtures in the query area
}
