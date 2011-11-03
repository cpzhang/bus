#include "RenderComponent.h"
#include "ProgramManager.h"
#include "Program.h"
#include "ServicesProvider.h"
#include "Shader.h"
#include "ShaderManager.h"
RenderComponent::RenderComponent()
{
    _vertices.push_back(Vertex(0.0, 0.0, 0.0));
    _vertices.push_back(Vertex(0.5, 0.0, 0.0));
    _vertices.push_back(Vertex(0.0, 0.5, 0.0));
    
    _programName = "fuck";

    _viewMatrix = Matrix4::IDENTITY;
    _modelMatrix.makeScale(Vector3(2.0, 2.0, 1.0));
    _projectionMatrix.makeOrtho(0, 480, 0, 320, 0, 1);
}

RenderComponent::~RenderComponent()
{
    
}

void RenderComponent::render()
{
    Program* p = ProgramManager::getInstancePtr()->getProgram(_programName);
    if (p)
    {
        p->apply();
        p->setVertexAttributePointer("aPosition", 3, GL_FLOAT, GL_FALSE, 0, &_vertices[0]);
	p->setUniformMatrixfv("uModel", 1, false, _modelMatrix.transpose()._m);
	p->setUniformMatrixfv("uView", 1, false, _viewMatrix.transpose()._m);
	p->setUniformMatrixfv("uProjection", 1, false, _projectionMatrix.transpose()._m);
        ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_TRIANGLES, 0, 3);
    }
}

void RenderComponent::setProgram(const std::string& name)
{
    _programName = name;
}
