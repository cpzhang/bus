#ifndef _ServicesProvider_
#define _ServicesProvider_

#include "IRender.h"
#include "Singleton.h"
struct IRender;
struct IServicesProvider
{
    virtual void setRender(eRender e) = 0;
    virtual IRender* getRender() = 0;
};

class ServicesProvider : public IServicesProvider, public Singleton<ServicesProvider>
{
public:
    ServicesProvider();
    ~ServicesProvider();

    virtual void setRender(eRender e);
    virtual IRender* getRender();
    
private:
    IRender*    _render;
};

#endif
