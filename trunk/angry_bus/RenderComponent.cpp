//
//  RenderComponent.cpp
//  angry_bus
//
//  Created by suning on 11-10-29.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "RenderComponent.h"
#include "ProgramManager.h"
#include "Program.h"
#include "ServicesProvider.h"
#include "Shader.h"
#include "ShaderManager.h"
RenderComponent::RenderComponent()
{
    _vertices.push_back(Vertex(0.0, 0.0, -1.0));
    _vertices.push_back(Vertex(0.5, 0.0, -1.0));
    _vertices.push_back(Vertex(0.0, 0.5, -1.0));
    
 
    {
        Shader* vs = ShaderManager::getInstancePtr()->createShader("fuck.vs");
        vs->setFile(vs->getName());
        vs->setType(GL_VERTEX_SHADER);
        vs->build();
    }
    
    {
        Shader* vs = ShaderManager::getInstancePtr()->createShader("fuck.fs");
        vs->setFile(vs->getName());
        vs->setType(GL_FRAGMENT_SHADER);
        vs->build();
    }
    
    _programName = "fuck";
    Program* p = ProgramManager::getInstancePtr()->createProgram(_programName);
    p->setVertexShader("fuck.vs");
    p->setFragmentShader("fuck.fs");
    p->build();
}

RenderComponent::~RenderComponent()
{
    
}

void RenderComponent::render()
{
    Program* p = ProgramManager::getInstancePtr()->getProgram(_programName);
    p->apply();
    
    IRender* r = ServicesProvider::getInstancePtr()->getRender();
    r->setVertexAttributePointer(0, 4, GL_FLOAT, GL_FALSE, 0, &_vertices[0]);
    
    r->drawArrays(GL_TRIANGLES, 0, 3);
}

void RenderComponent::setProgram(const std::string& name)
{
    _programName = name;
}
