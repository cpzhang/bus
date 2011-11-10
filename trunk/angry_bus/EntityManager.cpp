#include "EntityManager.h"
#include "Entity.h"
#include "b2Contact.h"
#include "ButtonComponent.h"
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

Entity* EntityManager::createEntity(std::string const &name, bool bRender, bool bPhyiscs, bool bButton)
{
    NameEntityMap::iterator it = _entities.find(name);
    if (it == _entities.end())
    {
        _entities[name] = new Entity;
        _entities[name]->create(bRender, bPhyiscs, bButton);
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
    EntityManager::getInstancePtr()->createEntity("background_entry_state", true, false, false)->setTexture("beijing01.png");
    EntityManager::getInstancePtr()->createEntity("background_contact_us", true, false, false)->setTexture("lianxiwomen.png");
    EntityManager::getInstancePtr()->createEntity("background_setting", true, false, false)->setTexture("settingBackground.png");
    EntityManager::getInstancePtr()->createEntity("background_playing", true, false, false)->setTexture("chebeijing.png");

    // button
    EntityManager::getInstancePtr()->createEntity("button_enter", true, false, true)->setTexture("start.png");
    EntityManager::getInstancePtr()->getEntity("button_enter")->setCallBack(new ButtonPushedCallBack_Enter);

    EntityManager::getInstancePtr()->createEntity("button_us", true, false, true)->setTexture("women.png");

    EntityManager::getInstancePtr()->createEntity("button_sound", true, false, true)->setTexture("shengyin1.png");
    EntityManager::getInstancePtr()->createEntity("button_setting", true, false, true)->setTexture("shezhi.png");
    EntityManager::getInstancePtr()->createEntity("button_score", true, false, true)->setTexture("fenshu.png");
    EntityManager::getInstancePtr()->createEntity("button_achievement", true, false, true)->setTexture("chengjiu.png");
    EntityManager::getInstancePtr()->createEntity("button_network", true, false, true)->setTexture("wangluo.png");
    
    EntityManager::getInstancePtr()->createEntity("button_back", true, false, true)->setTexture("fanhui.png");
    EntityManager::getInstancePtr()->getEntity("button_back")->setCallBack(new ButtonPushedCallBack_GotoEntryPoint);
    
    EntityManager::getInstancePtr()->createEntity("button_score", true, false, true)->setTexture("fenshu.png");

    
    // sprite
    EntityManager::getInstancePtr()->createEntity("sprite_tree_bamboo", true, false, false)->setTexture("zhuzi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_tree_maple", true, false, false)->setTexture("fengshu.png");
    EntityManager::getInstancePtr()->createEntity("sprite_car", true, false, false)->setTexture("xiaoche.png");
    EntityManager::getInstancePtr()->createEntity("sprite_leaf_purple", true, false, false)->setTexture("ziseyezi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_leaf_green", true, false, false)->setTexture("lvseyezi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_leaf_yellow", true, false, false)->setTexture("huangseyezi.png");
    EntityManager::getInstancePtr()->createEntity("sprite_bus", true, false, false)->setTexture("che.png");
}
