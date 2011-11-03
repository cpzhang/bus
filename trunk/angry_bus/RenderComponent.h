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
class RenderComponent : public IRenderComponent
{
public:
    RenderComponent();
    ~RenderComponent();
    
    void render();
    
    void setProgram(const std::string& name);
private:
    std::string _programName;
    std::vector<Vertex> _vertices;
    Matrix4 _viewMatrix;
    Matrix4 _modelMatrix;
    Matrix4 _projectionMatrix;
};

#endif
