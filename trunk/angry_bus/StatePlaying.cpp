#include "StatePlaying.h"
#include "EntityManager.h"
#include "Entity.h"
#include "Node.h"
#include "NodeManager.h"
#include "ButtonCallbackManager.h"
#include <sstream>
#include "PhysicsManager.h"
#include "Event.h"

StatePlaying::StatePlaying()
{
    {
        _uiRoot = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_playing");
        _uiRoot->setPosition(160, 240, 0);
        _uiRoot->setScale(320, 480, 1.0);
    }
    
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_bus");
        n->setPosition(80, 240, 0);
        n->setScale(160, 480, 1.0);
        _uiRoot->addChild(n);
    }
    
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_back_levelselectionstate");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_back"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to level selection state"));
        n->setPosition(16, 450, 0);
        n->setScale(32, 32, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_score_background");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_score_background"));
        n->setPosition(300, 50, 0);
        n->setScale(60, 86, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_score_001");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_score_0"));
        n->setPosition(300, 25, 0);
        n->setScale(30, 16, 1.0);
        _uiRoot->addChild(n);
    }
   
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_score_010");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_score_1"));
        n->setPosition(300, 43, 0);
        n->setScale(30, 16, 1.0);
        _uiRoot->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "sprite_score_100");
        n->setData(EntityManager::getInstancePtr()->getEntity("sprite_score_2"));
        n->setPosition(300, 60, 0);
        n->setScale(30, 16, 1.0);
        _uiRoot->addChild(n);
    }
    {
        _uiResult = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_result");
        _uiResult->setData(EntityManager::getInstancePtr()->getEntity("background_result"));
        _uiResult->setPosition(160, 240, 0);
        _uiResult->setScale(320, 160, 1.0);
        _uiResult->hide();
        _uiRoot->addChild(_uiResult);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Transformation, "background_success");
        n->setData(EntityManager::getInstancePtr()->getEntity("background_success"));
        n->setPosition(200, 240, 0);
        n->setScale(100, 100, 1.0);
        _uiResult->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_statePlaying_goOn");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_statePlaying_goOn"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to next level"));
        n->setPosition(130, 200 - 20, 0);
        n->setScale(32, 32, 1.0);
        _uiResult->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_statePlaying_again");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_statePlaying_again"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("do the same level again"));
        n->setPosition(130, 250 - 10, 0);
        n->setScale(32, 32, 1.0);
        _uiResult->addChild(n);
    }
    {
        Node<Entity>* n = NodeManager::getInstancePtr()->createNode(eNodeType_Button, "button_statePlaying_levelSelection");
        n->setData(EntityManager::getInstancePtr()->getEntity("button_statePlaying_levelSelection"));
        n->setCallBack(ButtonCallbackManager::getInstancePtr()->getCallback("go to level selection state"));
        n->setPosition(130, 300, 0);
        n->setScale(32, 32, 1.0);
        _uiResult->addChild(n);
    }
    
    {
        _ready_go = EntityManager::getInstancePtr()->createEntity("ready_go", true, false, false);
    }
    //
    _score = 0;
    {
        _scoreTextures.push_back("0.png");
        _scoreTextures.push_back("1.png");
        _scoreTextures.push_back("2.png");
        _scoreTextures.push_back("3.png");
        _scoreTextures.push_back("4.png");
        _scoreTextures.push_back("5.png");
        _scoreTextures.push_back("6.png");
        _scoreTextures.push_back("7.png");
        _scoreTextures.push_back("8.png");
        _scoreTextures.push_back("9.png");
    }
    {
        _clock = EntityManager::getInstancePtr()->createEntity("clock", true, false, false);
        _clock->setTexture("ui_miaobiao_1.png");
        _clock->setPosition(280, 450, 0);
        _clock->setScale(57, 31, 1);
    }
    {
        _count_down01 = EntityManager::getInstancePtr()->createEntity("count_down01", true, false, false);
        _count_down01->setPosition(280, 400, 0);
        _count_down01->setScale(30, 16, 1);
    }
    {
        _count_down10 = EntityManager::getInstancePtr()->createEntity("count_down10", true, false, false);
        _count_down10->setPosition(280, 420, 0);
        _count_down10->setScale(30, 16, 1);
    }
}
void StatePlaying::createPassengers(int num)
{
    if (num < 0)
    {
        return;
    }
    // clear the passagers first, and then fill it
    _passengers.clear();
    // check if we have enough passengers in pool; else create them
    if (num > _passengersPool.size())
    {
        int i = _passengersPool.size();
        for (; i <= num; ++i)
        {
            std::stringstream ss;
            ss<<_passengersPool.size();
            Entity* n = EntityManager::getInstancePtr()->createEntity(ss.str(), true, true, false);
            n->setBody(PhysicsManager::getInstancePtr()->createBody(300, 200));
            _passengersPool.push_back(n);
        }
    }
    // set texture
    switch (_scene) 
    {
        case eScene_City:
        {
            for (size_t i = 0; i != _passengersPool.size(); ++i)
            {
                if (_passengersPool[i])
                {
                    _passengersPool[i]->setExpression(eExpression_Normal, "xiongmao01.png");
                    _passengersPool[i]->setExpression(eExpression_Smile, "xiongmao_xiao01.png");
                    _passengersPool[i]->setExpression(eExpression_Normal);
                    
                }
            }
        }
            break;
        case eScene_WetLand:
        {
            for (size_t i = 0; i != _passengersPool.size(); ++i)
            {
                if (_passengersPool[i])
                {
                    _passengersPool[i]->setExpression(eExpression_Normal, "kulou2.png");
                    _passengersPool[i]->setExpression(eExpression_Smile, "kulou2.png");
                    _passengersPool[i]->setExpression(eExpression_Normal);
                    
                }
            }
        }
            break;    
        case eScene_Glacier:
        {
            for (size_t i = 0; i != _passengersPool.size(); ++i)
            {
                if (_passengersPool[i])
                {
                    _passengersPool[i]->setExpression(eExpression_Normal, "cry01.png");
                    _passengersPool[i]->setExpression(eExpression_Smile, "cry01.png");
                    _passengersPool[i]->setExpression(eExpression_Normal);
                    
                }
            }
        }
            break;    
            
        default:
            break;
    }

    // fill
    for (int i = 0; i != num; ++i)
    {
        // value property
        //_passengersPool[i]->setValue(eValueProperty_AddScores, 1);
        _passengersPool[i]->setValue(eValueProperty_AddSeconds, 3);
        _passengers.push_back(_passengersPool[i]);
    }
}
void StatePlaying::resetPassengers()
{
    for (size_t i = 0; i != _passengers.size(); ++i)
    {
        if (_passengers[i])
        {
            int x = 160 + rand()%160;
            int y = rand()%480;
            _passengers[i]->setPosition(x, y);
        }
    }
}
bool StatePlaying::isReady()
{
    return _IsReady;
}

bool StatePlaying::isInBus(Entity* e)
{
    Vector3 p = e->getPosition();
    if (p.x < 150)
    {
        return true;
    }
    return false;
}

int StatePlaying::get001(int score)
{
    return score - 100 * get100(score) - 10 * get010(score);
}

int StatePlaying::get010(int score)
{
    return (score - 100 * get100(score)) / 10;
}

int StatePlaying::get100(int score)
{
    return score / 100;    
}

StatePlaying::~StatePlaying()
{
    _uiRoot->release();
    _uiRoot = 0;
    //
    _uiResult->render();
    _uiResult = 0;
    //
    //for (size_t i = 0; i != _passengers.size(); ++i)
    //{
    //    if (_passengers[i])
    //    {
    //        delete _passengers[i];
    //        _passengers[i] = 0;
    //    }
    //}
    //_passengers.clear();
    //
    delete _ready_go;
    _ready_go = 0;
    //
    delete _clock;
    _clock = 0;
    //
    delete _count_down01;
    _count_down01 = 0;
    //
    delete _count_down10;
    _count_down10 = 0;
    //
    TimerManager::getInstancePtr()->removeTimer(&_ready_timer);
    TimerManager::getInstancePtr()->removeTimer(&_go_timer);
    TimerManager::getInstancePtr()->removeTimer(&_count_down_timer);
}

void StatePlaying::render()
{
    _uiRoot->render();
    for (size_t i = 0; i != _passengers.size(); ++i)
    {
        if (_passengers[i])
        {
            _passengers[i]->render();
        }
    }
    _ready_go->render();
    //
    _clock->render();
    //
    _count_down01->render();
    _count_down10->render();
    //
    _uiResult->render();
}

void StatePlaying::update(float secondsElapsed)
{
    _score = 0;
    _timer_offset = 0;
    _uiRoot->breadth_first(&Entity::update);
    for (size_t i = 0; i != _passengers.size(); ++i)
    {
        if (_passengers[i])
        {
            _passengers[i]->update();
            if(isInBus(_passengers[i]))
            {
                switch (_passengers[i]->getProperty())
                {
                    case eValueProperty_AddScores:
                    {
                        _score += _passengers[i]->getValue();
                    }
                    break;
                    case eValueProperty_AddSeconds:
                    {
                        if (!_passengers[i]->isInBus()) 
                        {
                            changeTimer(_passengers[i]->getValue());
                        }
                    }
                    break;
                    default:
                        break;
                }
                _passengers[i]->setExpression(eExpression_Smile);
                _passengers[i]->setInBus(true);
            }
            else
            {
                _passengers[i]->setExpression(eExpression_Normal);
                _passengers[i]->setInBus(false);
            }
        }
    }
    _working_time += _timer_offset;
    if (isWinner())
    {
        stopThisLevel();
    }
    _ready_go->update();
       
    //
    size_t index = get001(_score);
    _uiRoot->getNodeByName("sprite_score_001")->getData()->setTexture(_scoreTextures[index]);
    index = get010(_score);
    _uiRoot->getNodeByName("sprite_score_010")->getData()->setTexture(_scoreTextures[index]);
    index = get100(_score);
    _uiRoot->getNodeByName("sprite_score_100")->getData()->setTexture(_scoreTextures[index]);
    //
    _clock->update();
    //
    _count_down01->update();
    _count_down10->update();
    //
    _uiRoot->breadth_first(&Entity::update);
}

bool StatePlaying::touchBegin(float x, float y)
{
    return _uiRoot->touchBegin(x, y);
}

bool StatePlaying::touchMoved(float x, float y, float previousX, float previousY)
{
    return _uiRoot->touchMoved(x, y, previousX, previousY);
}

bool StatePlaying::touchEnd(float x, float y)
{
    return _uiRoot->touchEnd(x, y);
}

void StatePlaying::start()
{
    _uiRoot->setTransformation();
    _uiResult->setTransformation();
}

void StatePlaying::beginLevel()
{
    _working_time = 30;
    createPassengers(_level);
    resetPassengers();
    resetTimer();
    TimerManager::getInstancePtr()->removeTimer(&_ready_timer);
    TimerManager::getInstancePtr()->addTimer(&_ready_timer);
    TimerManager::getInstancePtr()->removeTimer(&_go_timer);
    TimerManager::getInstancePtr()->addTimer(&_go_timer);
    TimerManager::getInstancePtr()->removeTimer(&_count_down_timer);
    TimerManager::getInstancePtr()->addTimer(&_count_down_timer);
    _count_down01->hide();
    _count_down10->hide();
    _IsReady = false;
    _isTimeOut = false;
    _uiResult->hide();
    _ready_go->hide();
}
bool StatePlaying::loadScene(eScene c)
{
    _level = 1;
    beginLevel();
    _scene = c;
    switch (c) 
    {
        case eScene_City:
        {
            _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_playing_city"));
            _uiRoot->getNodeByName("sprite_bus")->setData(EntityManager::getInstancePtr()->getEntity("sprite_bus"));
            _uiRoot->getNodeByName("sprite_bus")->setPosition(80, 240, 0);
            _uiRoot->getNodeByName("sprite_bus")->setScale(160, 480, 1.0);
            for (size_t i = 0; i != _passengersPool.size(); ++i)
            {
                if (_passengersPool[i])
                {
                    _passengersPool[i]->setExpression(eExpression_Normal, "xiongmao01.png");
                    _passengersPool[i]->setExpression(eExpression_Smile, "xiongmao_xiao01.png");
                    _passengersPool[i]->setExpression(eExpression_Normal);

                }
            }
        }
        break;
        case eScene_WetLand:
        {
            _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_playing_wetLand"));
            _uiRoot->getNodeByName("sprite_bus")->setData(EntityManager::getInstancePtr()->getEntity("sprite_bus_wetLand"));
            _uiRoot->getNodeByName("sprite_bus")->setPosition(80, 240, 0);
            _uiRoot->getNodeByName("sprite_bus")->setScale(233, 480, 1.0);
            for (size_t i = 0; i != _passengersPool.size(); ++i)
            {
                if (_passengersPool[i])
                {
                    _passengersPool[i]->setExpression(eExpression_Normal, "kulou2.png");
                    _passengersPool[i]->setExpression(eExpression_Smile, "kulou2.png");
                    _passengersPool[i]->setExpression(eExpression_Normal);

                }
            }
        }
        break;    
        case eScene_Glacier:
        {
            _uiRoot->setData(EntityManager::getInstancePtr()->getEntity("background_playing_glacier"));
            _uiRoot->getNodeByName("sprite_bus")->setData(EntityManager::getInstancePtr()->getEntity("sprite_bus_glacier"));
            _uiRoot->getNodeByName("sprite_bus")->setPosition(80, 240, 0);
            _uiRoot->getNodeByName("sprite_bus")->setScale(194, 480, 1.0);
            for (size_t i = 0; i != _passengersPool.size(); ++i)
            {
                if (_passengersPool[i])
                {
                    _passengersPool[i]->setExpression(eExpression_Normal, "cry01.png");
                    _passengersPool[i]->setExpression(eExpression_Smile, "cry01.png");
                    _passengersPool[i]->setExpression(eExpression_Normal);

                }
            }
        }
        break;    
        
        default:
            break;
    }
    return true;
}
bool StatePlaying::isWinner()
{
    if (_level <= _score)
    {
        return true;
    }
    
    return false;
}
void StatePlaying::onWinner()
{
    EntityManager::getInstancePtr()->getEntity("background_success")->setTexture("ui_chenggong_xiao.png");
    _uiResult->getNodeByName("button_statePlaying_goOn")->show();
}
void StatePlaying::onLoser()
{
    EntityManager::getInstancePtr()->getEntity("background_success")->setTexture("ui_shibai_ku.png");    
    _uiResult->getNodeByName("button_statePlaying_goOn")->hide();
}
void StatePlaying::stopThisLevel()
{
    if (isWinner())
    {
        onWinner();
    }
    else
    {
        onLoser();
    }
    _isTimeOut = true;
    _IsReady = false;
    _uiResult->show();
    sEvent e;
    e.eventID = eEvent_LevelFinished;
    EventManager::getInstancePtr()->fireEvent(&e);
}
void StatePlaying::onTimer(int sequence)
{
    switch (sequence)
    {
        case 0:
        {
            _ready_go->setTexture("ready.png");
            _ready_go->setScale(100, 320, 0);
            _ready_go->show();
        }break;
        case 1:
        {
            _ready_go->setTexture("go.png");
            _ready_go->setScale(100, 130, 0);
        }break;
        case 2:
        {
            if (!_IsReady)
            {
                _IsReady = true;
                _ready_go->hide();
                _count_down01->show();
                _count_down10->show();
            }
            else
            {
                _working_time--;
                if (_working_time <= 0)
                {
                    stopThisLevel();
                }
            }
            
            _count_down01->setTexture(_scoreTextures[get001(_working_time)]);
            _count_down10->setTexture(_scoreTextures[get010(_working_time)]);
        }break;
            
        default:
            break;
    }
}

void StatePlaying::resetTimer()
{
    //
    _ready_timer._timer_handler = this;
    _ready_timer._sequence = 0;
    _ready_timer._last_call_stamp = 0.0;
    _ready_timer._first_call_stamp = 1;
    _ready_timer._interval = 1.0;
    _ready_timer._is_limit_how_many_times = true;
    _ready_timer._how_many_times_should_do = 1;
    //
    _go_timer._timer_handler = this;
    _go_timer._sequence = 1;
    _go_timer._last_call_stamp = 0.0;
    _go_timer._first_call_stamp = 2;
    _go_timer._interval = 1.0;
    _go_timer._is_limit_how_many_times = true;
    _go_timer._how_many_times_should_do = 1;
    //
    _count_down_timer._timer_handler = this;
    _count_down_timer._sequence = 2;
    _count_down_timer._last_call_stamp = 0.0;
    _count_down_timer._first_call_stamp = 3;
    _count_down_timer._interval = 1.0;
    _count_down_timer._is_limit_how_many_times = false;
    //_count_down_timer._how_many_times_should_do = _working_time + 1;
}

void StatePlaying::nextLevel()
{
    ++_level;
    beginLevel();
}

void StatePlaying::theSameLevelAgain()
{
    beginLevel();
}

void StatePlaying::changeTimer(int i)
{
    _timer_offset += i;
}