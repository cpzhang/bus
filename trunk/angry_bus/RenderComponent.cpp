#include "RenderComponent.h"
#include "ProgramManager.h"
#include "Program.h"
#include "ServicesProvider.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "TextureManager.h"
RenderComponent::RenderComponent()
:_tex(0), _angle(0.0f), _position(Vector3(160.0, 240.0, 0.0)), _scale(Vector3(32.0, 32.0, 1.0))
{
    //
    {
        _vertices.push_back(Vertex(-0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5,  0.5, 0.0));
        
        _vertices.push_back(Vertex(-0.5, -0.5, 0.0));
        _vertices.push_back(Vertex( 0.5,  0.5, 0.0));
        _vertices.push_back(Vertex(-0.5,  0.5, 0.0));
        
        _texCoords.push_back(Vector2(0.0, 1.0));
        _texCoords.push_back(Vector2(1.0, 1.0));
        _texCoords.push_back(Vector2(1.0, 0.0));
        
        _texCoords.push_back(Vector2(0.0, 1.0));
        _texCoords.push_back(Vector2(1.0, 0.0));
        _texCoords.push_back(Vector2(0.0, 0.0));
    }
    
    _programName = "fuck";

    _viewMatrix = Matrix4::IDENTITY;
    _projectionMatrix.makeOrtho(0, 320, 0, 480, 0, 1);
    updateModelMatrix();
}

RenderComponent::~RenderComponent()
{
    if (_tex)
    {
        TextureManager::getInstancePtr()->discardTexture(_tex);
    }
}

void RenderComponent::setScale(float sx, float sy, float sz)
{
    _scale = Vector3(sx, sy, sz);
    updateModelMatrix();
}

void RenderComponent::setScale(const Vector3 &s)
{
    _scale = s;
    updateModelMatrix();
}

void RenderComponent::setPosition(float x, float y, float z)
{
    _position = Vector3(x, y, z);
    updateModelMatrix();
}

void RenderComponent::setPosition(const Vector3 &p)
{
    _position = p;
    updateModelMatrix();
}

void RenderComponent::setRotation(float angle)
{
    _angle = angle;
    updateModelMatrix();
}

void RenderComponent::updateModelMatrix()
{
    Matrix4 t;
    t.makeTrans(_position);
    
    Matrix4 r;
    r.makeRotateZ(_angle);
    
    Matrix4 s;
    s.makeScale(_scale);
    
    _modelMatrix = t * r * s;
}

bool RenderComponent::setTexture(std::string const &fileName)
{
    if (_tex)
    {
        TextureManager::getInstancePtr()->discardTexture(_tex);
    }
    //
    _tex = TextureManager::getInstancePtr()->createTextureFromImageFile(fileName);
    
    return _tex != 0;
}

void RenderComponent::update()
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
        if (_tex)
        {
            _tex->apply(0);
            p->setUniformi("uSampler", 0);
        }
        
        ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_TRIANGLES, 0, 6);
        //glBindTexture(GL_TEXTURE_2D, 0);
        p->disableVertexAttribArray("aPosition");
        p->disableVertexAttribArray("aTexCoord");
    }
}

void RenderComponent::setProgram(const std::string& name)
{
    _programName = name;
}
