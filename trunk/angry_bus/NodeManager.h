#ifndef _NodeManager_
#define _NodeManager_
#include "Singleton.h"
#include "Node.h"
#include <map>

class NodeManager: public Singleton<NodeManager>
{
public:
    NodeManager();
    ~NodeManager();

    Node<Entity>* createNode(eNodeType e, const std::string& name);
    Node<Entity>* getNode(const std::string& name);

private:
    typedef std::map<std::string, Node<Entity>*> NameNodeMap;
    NameNodeMap _nodes;
};
#endif
