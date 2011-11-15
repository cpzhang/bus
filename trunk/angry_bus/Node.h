#ifndef _Node_
#define _Node_

#include <vector>
#include <string>
#include "Vector3.h"
#include "Entity.h"
#include "ITouch.h"

template <class T>
class Node: public ITouch
{
public:
    Node(const std::string& name)
	:_name(name), _visible(true)
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
    virtual void setTransformation(float s=1.0){};
    
    virtual bool touchBegin(float x, float y)
    {
        if (_visible) 
        {
            if(touchBeginImp(x, y))
            {
                return true;
            }
            else
            {
                //
                for(size_t i = 0; i != getChildrenNumber(); ++i)
                {
                    if(_children[i]->touchBeginImp(x, y))
                        return true;
                }
            }
        }
        return false;
    }
    virtual bool touchMoved(float x, float y, float previousX, float previousY)
    {
        if (_visible) 
        {
            if(touchMovedImp(x, y, previousX, previousY))
            {
                return true;
            }
            else
            {
                //
                for(size_t i = 0; i != getChildrenNumber(); ++i)
                {
                    if(_children[i]->touchMovedImp(x, y, previousX, previousY))
                        return true;
                }
            }
        }
        return false;
    }

    virtual bool touchEnd(float x, float y)
    {
        if (_visible) 
        {
            if(touchEndImp(x, y))
            {
                return true;
            }
            else
            {
                //
                for(size_t i = 0; i != getChildrenNumber(); ++i)
                {
                    if(_children[i]->touchEndImp(x, y))
                        return true;
                }
            }
        }
        return false;
    }

    
    virtual bool touchBeginImp(float x, float y){return false;}
    virtual bool touchMovedImp(float x, float y, float previousX, float previousY){return false;}
    virtual bool touchEndImp(float x, float y){return false;}
    
    
    void hide(){_visible = false;}
    void show(){_visible = true;}
    
    Node* getNodeByName(const std::string& name)
    {
        if (_name == name)
        {
            return this;
        }
        //
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            Node* n = _children[i]->getNodeByName(name);
            if(n)
                return n;
        }
        return 0;
    }
protected:
    std::vector<Node*> _children;
    Node* _parent;
    T* _data;
    std::string _name;
    bool _visible;
};

//template<class T>
class TransformationNode: public Node<Entity>
{
public:    
    inline TransformationNode(const std::string& name)
	:_angle(0.0), Node<Entity>(name)
    {
        
    }
    
    ~TransformationNode(){};
    
    void render()
    {
        if (_visible)
        {
            _data->render();
            for(size_t i = 0; i != getChildrenNumber(); ++i)
            {
                _children[i]->render();
            }
        }
    }
    virtual void setTransformation(float s=1.0)
    {
        _data->setPosition(_position);
        _data->setScale(_scale * s);
        _data->setRotation(_angle);
        for(size_t i = 0; i != getChildrenNumber(); ++i)
        {
            _children[i]->setTransformation(s);
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
    
protected:
    Vector3 _position;
    Vector3 _scale;
    float  _angle;
};

class ButtonNode: public TransformationNode
{
public:
    ButtonNode(const std::string& name);
    ~ButtonNode();
    
    virtual bool touchBeginImp(float x, float y);
    virtual bool touchMovedImp(float x, float y, float previousX, float previousY);
    virtual bool touchEndImp(float x, float y);
    
private:
    bool isInside(float x, float y);
    void onHover();
    void onHoverEnd();
    void onPushed();
    
private:
    eButtonState _state;
};
#endif
