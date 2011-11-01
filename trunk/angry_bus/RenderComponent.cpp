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
    
    _programName = "fuck";
}

RenderComponent::~RenderComponent()
{
    
}

void RenderComponent::render()
{
    Program* p = ProgramManager::getInstancePtr()->getProgram(_programName);
    p->apply();
    p->setVertexAttributePointer("aPosition", 4, GL_FLOAT, GL_FALSE, 0, &_vertices[0]);
    IRender* r = ServicesProvider::getInstancePtr()->getRender();
    r->drawArrays(GL_TRIANGLES, 0, 3);
}

void RenderComponent::setProgram(const std::string& name)
{
    _programName = name;
}
