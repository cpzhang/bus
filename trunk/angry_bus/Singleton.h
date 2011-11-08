#ifndef __SINGLETON_
#define __SINGLETON_
#include <cassert>
/// 扩展的单实体模板，不关心对象的创建和销毁
/// 采用外部new和delete，这种单实体的好处是外部能控制构造和析构的顺序
template <typename T>
class Singleton
{
protected:
    static T*	_instance;
    
public:
    Singleton()
    {
        assert(!_instance);
        _instance = static_cast<T*>(this);

    }
    
    ~Singleton()
    {
        assert(_instance);
        _instance = 0;
    }
    
    static T& getInstance()		{ assert(_instance); return (*_instance); }
    static T* getInstancePtr()	{ return _instance; }
};

template <typename T> T* Singleton<T>::_instance = 0;
#endif
