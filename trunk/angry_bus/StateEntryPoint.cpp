#include "StateEntryPoint.h"
StateEntryPoint::StateEntryPoint()
{
    _uiRoot = new Node<Entity*>;
    Entity* e = EntityManager::getInstancePtr()->createEntity("Dummy");
    _uiRoot->setData(e);
}

StateEntryPoint::~StateEntryPoint()
{
    
}
void renderNode(Node* n)
{
    if(!n) return;
    if(n->getData())
	n->getData()->render();
    for(size_t i = 0; i != n->getChildrenNumber(); ++i)
    {
	renderNode(n->getChild(i));
    }
}
void StateEntryPoint::render()
{
    // renderNode(_uiRoot);
    _uiRoot->breadth_first(&Entity::render);
}
