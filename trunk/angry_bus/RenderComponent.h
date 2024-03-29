#ifndef _RenderComponent_
#define _RenderComponent_

#include "IComponent.h"
#include <string>
#include <vector>
#include "Vertex.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
class Texture;
class RenderComponent : public IRenderComponent
{
public:
    RenderComponent();
    ~RenderComponent();
    
    virtual void update();
    
    virtual void render(const Color& c = Color::White);
    virtual void setProgram(const std::string& name);
    virtual bool setTexture(const std::string& fileName);
    virtual void setScale(float sx, float sy, float sz);
    virtual void setPosition(float x, float y, float z);
    virtual Vector3 getPosition();
    virtual void setRotation(float angle);
    virtual void setScale(const Vector3& s);
    virtual void setPosition(const Vector3& p);
    virtual bool isInside(float x, float y);
    virtual Vector3 getScale();
private:
    void updateModelMatrix();
private:
    std::string _programName;
    std::vector<Vertex> _vertices;
    std::vector<Vector2> _texCoords;
    Matrix4 _viewMatrix;
    Matrix4 _modelMatrix;
    Matrix4 _projectionMatrix;
    Texture* _tex;
    std::string _texName;
    Vector3 _position;
    Vector3 _scale;
    float   _angle;
};

#endif
