#include "NodeManager.h"
NodeManager::NodeManager()
{
}
NodeManager::~NodeManager()
{
    NameNodeMap::iterator it = _nodes.begin();
    for (; it != _nodes.end(); ++it)
    {
        Node* e = it->second;
        if (e)
        {
            delete e;
            e = 0;
        }
    }
    //
    _nodes.clear();
}
Node* createNode(eNodeType e, const std::string& name)
{
    NameNodeMap::iterator it = _nodes.find(name);
    if(it == _nodes.end())
    {
	switch(e)
	{
	case eNodeType_Transformation:
	    _nodes[name] = new TransformationNode(name);
	    break;
	case eNodeType_Button:
	    _nodes[name] = new ButtonNode(name);
	    break;
	}
    }
    return _nodes[name];
}

Node* NodeManager::getNode(const std::string& name)
{
    NameNodeMap::iterator it = _nodes.find(name);
    if(it != _nodes.end())
    {
	return it->second;
    }
    return 0;
}
