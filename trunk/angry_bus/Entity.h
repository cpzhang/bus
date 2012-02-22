#ifndef _Entity_
#define _Entity_

#include "IComponent.h"
#include "b2Body.h"
#include "Vector3.h"
#include <string>
#include <vector>
enum eExpression
{
    eExpression_Normal = 0,
    eExpression_Cry,
    eExpression_Smile,
    eExpression_Stun,
    eExpression_Playing,
    eExpression_Size,
};
enum eValueProperty
{
    eValueProperty_AddScores,
    eValueProperty_AddSeconds,
};
class Entity: public IRenderComponent, public IPhysicsComponent
{
public:
    Entity();
    ~Entity();
    
    bool create(bool bRender, bool bPhysics, bool bButton);
    
    virtual void update();
    //
    virtual void render(const Color& c = Color::White);
    virtual void setProgram(const std::string& name);
    virtual bool setTexture(const std::string& fileName);
    virtual void setScale(float sx, float sy, float sz);
    virtual void setScale(const Vector3& s);
    virtual void setPosition(float x, float y, float z);
    virtual void setPosition(const Vector3& p);
    virtual void setRotation(float angle);
    virtual bool isInside(float x, float y);
    virtual Vector3 getScale();
    virtual Vector3 getPosition();
    //
    virtual void setBody(b2Body* b);
    virtual void startContact();
    virtual void endContact();
    virtual void setPosition(float x, float y);
    void hide();
    void show();
    void setExpression(eExpression e);
    void setExpression(eExpression e, const std::string& s);
    void setValue(eValueProperty property, int value);
    int  getValue();
    eValueProperty getProperty();
    void setInBus(bool inBus);
    bool isInBus();
private:
    IRenderComponent*   _render_component;
    IPhysicsComponent*  _physics_component;
    std::string _expressions[eExpression_Size];
    bool _hide;
    eValueProperty _property;
    int _value;
    bool _isInBus;
};

class KeyFrameEntity
{
public:
    KeyFrameEntity();
    ~KeyFrameEntity();
    
private:
    Entity* _entity;
    typedef std::vector<std::string> KeyFrameTextureVector;
    KeyFrameTextureVector _frames[eExpression_Size];
};
#endif
