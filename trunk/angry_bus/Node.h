#ifndef _Node_
#define _Node_

#include <vector>

template <class T>
class Node
{
public:
    Node()
    {
        
    }
    
    ~Node()
    {
        
    }
    
    void addChild(Node* n)
    {
        _children.push_back(n);
    }
    
    void removeChild(Node* n)
    {
        for (std::vector<Node*> i = _children.begin(); i != _children.end(); ++i)
        {
            if (n == *i)
            {
                _children.erase(i);
                return;
            }
        }
    }
    
    size_t getChildrenNumber()
    {
        return _children.size();
    }
    
    Node* getChild(size_t index)
    {
        return _children[index];
    }
    
    void setData(T* d)
    {
        _data = d;
    }
    
    T* getData()
    {
        return _data;
    }
    
    typedef void (T::*do_void_void)();
    void breadth_first(do_void_void f)
    {
        if(_data)
            (_data->*f)();
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->breadth_first(f);
        }
    }
    void release()
    {
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->release();
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
