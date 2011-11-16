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

    Node* createNode(eNodeType e, const std::string& name);
    Node* getNode(const std::string& name);

private:
    typedef std::map<std::string, Node*> NameNodeMap;
    NameNodeMap _nodes;
};
#endif
