#ifndef _Node_
#define _Node_

#include <vector>

template <class T>
class Node
{
public:
    Node();
    ~Node();

    void addChild(Node* n);
    void removeChild(Node* n);
    size_t getChildrenNumber();
    Node* getChild(size_t index);
    void setData(T* d);
    T* getData();
    typedef void T::*do_void_void();
    void breadth_first(do_void_void)
    {
	if(!n) return;
	if(n->getData())
	    n->getData()->*do_void_void();
	for(size_t i = 0; i != getChildrenNumber(); ++i)
	{
	    getChild(i)->breadth_first(do_void_void);
	}
    }
    void release()
    {
	for(size_t i = 0; i != getChildrenNumber(); ++i)
	{
	    getChild(i)->release();
	}
	_children.clear();
	delete this;
    }
private:
    std::vector<Node*> _children;
    Node* _parent;
    T* _data;
};
#endif
