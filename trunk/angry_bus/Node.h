#ifndef _Node_
#define _Node_

#include <vector>
#include <string>
#include "Vector3.h"
#include "Entity.h"

template <class T>
class Node
{
public:
    Node()
    {
        
    }
    Node(const std::string& name)
	:_name(name)
    {
        
    }
    
    virtual ~Node()
    {
        
    }
    
    virtual void addChild(Node* n)
    {
        _children.push_back(n);
    }
    
    virtual void removeChild(Node* n)
    {
        typename std::vector<Node*>::iterator it = _children.begin();
        for (; it != _children.end(); ++it)
        {
            if (n == *it)
            {
                _children.erase(it);
                return;
            }
        }
    }
    
    virtual size_t getChildrenNumber()
    {
        return _children.size();
    }
    
    virtual Node* getChild(size_t index)
    {
        return _children[index];
    }
    
    virtual void setData(T* d)
    {
        _data = d;
    }
    
    virtual T* getData()
    {
        return _data;
    }
    
    typedef void (T::*do_void_void)();
    virtual void breadth_first(do_void_void f)
    {
        if(_data)
            (_data->*f)();
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->breadth_first(f);
        }
    }
    typedef bool (T::*do_bool_float_float)(float, float);
    virtual bool breadth_first(do_bool_float_float f, float x, float y)
    {
        if(_data && ((_data->*f)(x, y)))
            return true;
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            if(_children[i]->breadth_first(f, x, y))
                return true;
        }
        return false;
    }
    typedef bool (T::*do_bool_float_float_float_float)(float, float, float, float);
    virtual bool breadth_first(do_bool_float_float_float_float f, float x, float y, float previousX, float previousY)
    {
        if(_data && ((_data->*f)(x, y, previousX, previousY)))
            return true;
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            if(_children[i]->breadth_first(f, x, y, previousX, previousY))
                return true;
        }
        return false;
    }
    virtual void release()
    {
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->release();
        }
        _children.clear();
        delete this;
    }
    virtual void render(){};
    virtual void setTransformation(){};
protected:
    std::vector<Node*> _children;
    Node* _parent;
    T* _data;
    std::string _name;
};

//template<class T>
class TransformationNode: public Node<Entity>
{
public:    
    inline TransformationNode(const std::string& name)
    :_angle(0.0)
    {
        
    }

    ~TransformationNode(){};
    
    void render()
    {
        _data->render();
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->render();
        }
    }
    virtual void setTransformation()
    {
        _data->setPosition(_position);
        _data->setScale(_scale);
        _data->setRotation(_angle);
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->setTransformation();
        }
    }
    void setScale(float sx, float sy, float sz)
    {
        _scale.x = sx;
        _scale.y = sy;
        _scale.z = sz;
    }
    void setPosition(float x, float y, float z)
    {
        _position.x = x;
        _position.y = y;
        _position.z = z;
    }
    void setRotation(float angle)
    {
        _angle = angle;
    }
    
private:
    Vector3 _position;
    Vector3 _scale;
    float  _angle;
};
#endif
