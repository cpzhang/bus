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

void EntityManager::createUI()
{
    // background
    EntityManager::getInstancePtr()->createEntity("background_entry_state")->setTexture("beijing.png");
    EntityManager::getInstancePtr()->createEntity("background_contact_us")->setTexture("lixiwomen.png");
    EntityManager::getInstancePtr()->createEntity("background_setting")->setTexture("settingBackground.png");

    // button
    EntityManager::getInstancePtr()->createEntity("button_enter")->setTexture("start.png");
    EntityManager::getInstancePtr()->createEntity("button_us")->setTexture("women.png");

    EntityManager::getInstancePtr()->createEntity("button_sound")->setTexture("shengyin1.png");
    EntityManager::getInstancePtr()->createEntity("button_setting")->setTexture("shezhi.png");
    EntityManager::getInstancePtr()->createEntity("button_score")->setTexture("fenshu.png");
    EntityManager::getInstancePtr()->createEntity("button_achievement")->setTexture("chengjiu.png");
    EntityManager::getInstancePtr()->createEntity("button_network")->setTexture("wangluo.png");
    EntityManager::getInstancePtr()->createEntity("button_back")->setTexture("fanhui.png");
    EntityManager::getInstancePtr()->createEntity("button_score")->setTexture("fenshu.png");
    EntityManager::getInstancePtr()->createEntity("button_score")->setTexture("fenshu.png");
    
    // sprite
    EntityManager::getInstancePtr()->createEntity("sprite_tree_bamboo")->setTexture("zhuzi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_tree_maple")->setTexture("fengshu.png");
    EntityManager::getInstancePtr()->createEntity("sprite_car")->setTexture("xiaoche.png");
    EntityManager::getInstancePtr()->createEntity("sprite_leaf_purple")->setTexture("ziseyezi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_leaf_green")->setTexture("lvseyezi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_leaf_yellow")->setTexture("huangseyezi.png");
}
