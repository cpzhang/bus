#include "bootstrapper.h"
#include "ServicesProvider.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ShaderManager.h"
#include "ProgramManager.h"
#include "TextureManager.h"
#include "Shader.h"
#include <iostream>
#include "StateMachine.h"
#include "NodeManager.h"
#include "ButtonCallbackManager.h"
#include "SoundManager.h"
#include "PhysicsManager.h"
#include "Timer.h"
#include "IState.h"
#include "Event.h"
BootStrapper::BootStrapper()
{
    
}

BootStrapper::~BootStrapper()
{
    
}

void BootStrapper::applyRender(eRender e)
{
    ServicesProvider::getInstancePtr()->setRender(e);
}

bool BootStrapper::initSingletons()
{
    new EventManager;
    new TimerManager;
    new ServicesProvider;
    new EntityManager;
    new ShaderManager;
    new ProgramManager;
    new TextureManager;
    new StateMachine;
    new NodeManager;
    new ButtonCallbackManager;
    new SoundManager;
    new PhysicsManager;

    return true;
}

bool BootStrapper::create()
{
    //
    if (!SoundManager::getInstancePtr()->create())
    {
        return false;
    }
    SoundManager::getInstancePtr()->play();
    //
    ButtonCallbackManager::getInstancePtr()->initCallbacks();
    
    //
    EntityManager::getInstancePtr()->createUI();
    
    //
    StateMachine::getInstancePtr()->createStates();
    StateMachine::getInstancePtr()->goNext(eState_EntryPoint);
    
    //
    registerPrograms();
    
    //
    ServicesProvider::getInstancePtr()->getRender()->setClearColor(0, 0, 0, 1.0);
    
    //
    
    return true;
}

void BootStrapper::destroy()
{
    delete ProgramManager::getInstancePtr();
    delete ShaderManager::getInstancePtr();
    delete ServicesProvider::getInstancePtr();
    delete EntityManager::getInstancePtr();
    delete StateMachine::getInstancePtr();
    delete NodeManager::getInstancePtr();
    delete ButtonCallbackManager::getInstancePtr();
    delete SoundManager::getInstancePtr();
    delete PhysicsManager::getInstancePtr();
    delete TimerManager::getInstancePtr();
    delete EventManager::getInstancePtr();
}
void BootStrapper::run(float secondsElapsed)
{
    update(secondsElapsed);
    render();
}

void BootStrapper::update(float secondsElapsed)
{
    TimerManager::getInstancePtr()->update(secondsElapsed);
    PhysicsManager::getInstancePtr()->update(secondsElapsed);
    StateMachine::getInstancePtr()->update(secondsElapsed);
}

void BootStrapper::render()
{
    ServicesProvider::getInstance().getRender()->beginFrame(true, false);
    StateMachine::getInstancePtr()->render();
    PhysicsManager::getInstancePtr()->render();
    ServicesProvider::getInstance().getRender()->endFrame();
}

void BootStrapper::setViewPort(int width, int height)
{
    ServicesProvider::getInstancePtr()->getRender()->setViewPort(width, height);
}

bool BootStrapper::registerPrograms()
{
    //
    
    if (0) 
    {
        if(!ShaderManager::getInstancePtr()->createAndBuildShader("vs", "fuck.vs", Shader::eShaderType_Vertex)) return false;
        if(!ShaderManager::getInstancePtr()->createAndBuildShader("fs", "fuck.fs", Shader::eShaderType_Fragment)) return false;
        if(!ProgramManager::getInstancePtr()->createAndBuildProgram("fuck", "vs", "fs")) return false;
    }
    
    //
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("diffuse_vs", "diffuse.vs", Shader::eShaderType_Vertex)) return false;
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("diffuse_fs", "diffuse.fs", Shader::eShaderType_Fragment)) return false;
    if(!ProgramManager::getInstancePtr()->createAndBuildProgram("diffuse", "diffuse_vs", "diffuse_fs")) return false;
    
    //
    //
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("texture_vs", "texture.vs", Shader::eShaderType_Vertex)) return false;
    if(!ShaderManager::getInstancePtr()->createAndBuildShader("texture_fs", "texture.fs", Shader::eShaderType_Fragment)) return false;
    if(!ProgramManager::getInstancePtr()->createAndBuildProgram("texture", "texture_vs", "texture_fs")) return false;
    
    
    return true;
}

bool BootStrapper::touchBegin(float x, float y)
{
    StateMachine::getInstancePtr()->touchBegin(x, y);
    if (IState::_IsReady)
    {
        PhysicsManager::getInstancePtr()->touchBegin(x, y);
    }
    
    return true;
}

bool BootStrapper::touchEnd(float x, float y)
{
    StateMachine::getInstancePtr()->touchEnd(x, y);
    if (IState::_IsReady)
        PhysicsManager::getInstancePtr()->touchEnd(x, y);
    return true;
}

bool BootStrapper::touchMoved(float x, float y, float previousX, float previousY)
{    
    StateMachine::getInstancePtr()->touchMoved(x, y, previousX, previousY);
    if (IState::_IsReady)
        PhysicsManager::getInstancePtr()->touchMoved(x, y, previousX, previousY);
    return true;
}

void BootStrapper::memoryWarning()
{
    return;
}
