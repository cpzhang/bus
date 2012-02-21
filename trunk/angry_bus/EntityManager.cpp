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
    createEntity("background_entry_state", true, false, false)->setTexture("beijing.png");
    createEntity("background_contact_us", true, false, false)->setTexture("aboutus.png");
    createEntity("background_setting", true, false, false)->setTexture("settingBackground.png");
    createEntity("background_playing_city", true, false, false)->setTexture("chebeijing.png");
    createEntity("background_playing_wetLand", true, false, false)->setTexture("jiangshizhidi.png");
    createEntity("background_playing_glacier", true, false, false)->setTexture("bingchuan.png");
    createEntity("background_selection", true, false, false)->setTexture("xuanguanbingjing.png");
    createEntity("background_result", true, false, false)->setTexture("ui_beijing01.png");
    createEntity("background_success", true, false, false)->setTexture("ui_chenggong_xiao.png");

    // button
    createEntity("button_enter", true, false, true)->setTexture("start.png");
    createEntity("button_us", true, false, true)->setTexture("women.png");
    createEntity("button_sound", true, false, true)->setTexture("shengyin1.png");
    createEntity("button_setting", true, false, true)->setTexture("shezhi.png");
    createEntity("button_score", true, false, true)->setTexture("fenshu.png");
    createEntity("button_achievement", true, false, true)->setTexture("chengjiu.png");
    createEntity("button_network", true, false, true)->setTexture("wangluo.png");
    createEntity("button_back", true, false, true)->setTexture("fanhui.png");
    createEntity("button_city", true, false, true)->setTexture("ui_chengshi.png");
    createEntity("button_wetLand", true, false, true)->setTexture("ui_shidi_01.png");
    createEntity("button_glacier", true, false, true)->setTexture("ui_bingchuan_01.png");
    createEntity("button_spaceStation", true, false, true)->setTexture("ui_kongjianzhan_02.png");
    createEntity("button_body", true, false, true)->setTexture("ui_renti.png");
    createEntity("button_ant", true, false, true)->setTexture("ui_yixue_02.png");
    createEntity("button_statePlaying_goOn", true, false, true)->setTexture("ui_fanhuizhujiemian.png");
    createEntity("button_statePlaying_again", true, false, true)->setTexture("ui_chonglai.png");
    createEntity("button_statePlaying_levelSelection", true, false, true)->setTexture("ui_fahuixuanguan.png");
    
    // sprite
    createEntity("sprite_tree_bamboo", true, false, false)->setTexture("zhuzi.png");
    createEntity("sprite_tree_maple", true, false, false)->setTexture("fengshu.png");
    createEntity("sprite_tree_bamboo_1", true, false, false)->setTexture("zhuzi.png");
    createEntity("sprite_tree_maple_1", true, false, false)->setTexture("fengshu.png");
    createEntity("sprite_car", true, false, false)->setTexture("xiaoche.png");
    createEntity("sprite_leaf_purple", true, false, false)->setTexture("ziseyezi.png");
    createEntity("sprite_leaf_green", true, false, false)->setTexture("lvseyezi.png");
    createEntity("sprite_leaf_yellow", true, false, false)->setTexture("huangseyezi.png");
    createEntity("sprite_bus", true, false, false)->setTexture("che.png");
    createEntity("sprite_bus_wetLand", true, false, false)->setTexture("bus_wetLand.png");
    createEntity("sprite_bus_glacier", true, false, false)->setTexture("xuediche.png");
    createEntity("sprite_score_background", true, false, false)->setTexture("ui_fenshuqi.png");
    createEntity("sprite_score_0", true, false, false)->setTexture("0.png");
    createEntity("sprite_score_1", true, false, false)->setTexture("0.png");
    createEntity("sprite_score_2", true, false, false)->setTexture("0.png");
}
