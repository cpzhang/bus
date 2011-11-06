//
//  RenderComponent.h
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
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
    
    virtual void render();
    virtual void setProgram(const std::string& name);
    virtual bool setTexture(const std::string& fileName);
    virtual void setScale(float sx, float sy, float sz);
    virtual void setPosition(float x, float y, float z);
    virtual void setRotation(float angle);
    
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
    Vector3 _position;
    Vector3 _scale;
    float   _angle;
};

#endif
