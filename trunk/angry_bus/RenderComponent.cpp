#include "RenderComponent.h"
#include "ProgramManager.h"
#include "Program.h"
#include "ServicesProvider.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "TextureManager.h"
RenderComponent::RenderComponent()
{
    if (0)
    {
        _vertices.push_back(Vertex(-0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5,  0.5, 0.0));
        
        _vertices.push_back(Vertex(-0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5,  0.5, 0.0));
        _vertices.push_back(Vertex(-0.5,  0.5, 0.0));
    }
    else
    {
        _vertices.push_back(Vertex(-0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5,  0.5, 0.0));
        
        _vertices.push_back(Vertex(-0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5,  0.5, 0.0));
        _vertices.push_back(Vertex(-0.5,  0.5, 0.0));
        
        _texCoords.push_back(Vector2(0.0, 0.0));
        _texCoords.push_back(Vector2(1.0, 0.0));
        _texCoords.push_back(Vector2(1.0, 1.0));
        
        _texCoords.push_back(Vector2(0.0, 0.0));
        _texCoords.push_back(Vector2(1.0, 1.0));
        _texCoords.push_back(Vector2(0.0, 1.0));
    }
    
    _programName = "fuck";

    _viewMatrix = Matrix4::IDENTITY;
    Matrix4 t;
    t.makeTrans(160, 80, 0);
    _modelMatrix.makeScale(Vector3(60.0, 100.0, 1.0));
    _modelMatrix = t * _modelMatrix;
    _projectionMatrix.makeOrtho(0, 320, 0, 480, 0, 1);
    
    //
    _tex = TextureManager::getInstancePtr()->createTextureFromImageFile("Default.png");
}

RenderComponent::~RenderComponent()
{
    
}

void RenderComponent::render()
{
   
    if (0) 
    {
        Program* p = ProgramManager::getInstancePtr()->getProgram(_programName);
        p->apply();
        p->setVertexAttributePointer("aPosition", 3, GL_FLOAT, GL_FALSE, 0, &_vertices[0]);
        Matrix4 mv = _modelMatrix * _viewMatrix;
        p->setUniformMatrixfv("uModelView", 1, false, mv.transpose()._m);
        p->setUniformMatrixfv("uProjection", 1, false, _projectionMatrix.transpose()._m);
        ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_TRIANGLES, 0, 6);
    }
    else
    {
        _programName = "texture";
        Program* p = ProgramManager::getInstancePtr()->getProgram(_programName);
        p->apply();
        p->setVertexAttributePointer("aPosition", 3, GL_FLOAT, GL_FALSE, 0, &_vertices[0]);
        p->setVertexAttributePointer("aTexCoord", 2, GL_FLOAT, GL_FALSE, 0, &_texCoords[0]);
        Matrix4 mv = _modelMatrix * _viewMatrix;
        p->setUniformMatrixfv("uModelView", 1, false, mv.transpose()._m);
        p->setUniformMatrixfv("uProjection", 1, false, _projectionMatrix.transpose()._m);
        //
        _tex->apply(0);
        p->setUniformi("uSampler", 0);
        
        ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_TRIANGLES, 0, 6);
    }
}

void RenderComponent::setProgram(const std::string& name)
{
    _programName = name;
}
