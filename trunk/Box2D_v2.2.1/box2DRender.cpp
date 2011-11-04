#include "box2DRender.h"
#include "ProgramManager.h"
#include "Program.h"
#include "ServicesProvider.h"
box2DRender::box2DRender()
{
    _mvp.makeOrtho(0, 320, 0, 480, 0, 1);
}

box2DRender::~box2DRender()
{
    
}

void box2DRender::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    Program* p = ProgramManager::getInstancePtr()->getProgram("diffuse");
    if (p)
    {
        p->apply();
        p->setVertexAttributePointer("aPosition", 2, GL_FLOAT, GL_FALSE, 0, vertices);
        p->setVertexAttribf("aColor", color.r, color.g, color.b, 1.0);
        p->setUniformMatrixfv("uModelViewProjection", 1, false, _mvp.transpose()._m);

        ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_LINE_LOOP, 0, vertexCount);
    }
}

void box2DRender::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Program* p = ProgramManager::getInstancePtr()->getProgram("diffuse");
    if (p)
    {
        p->apply();
        p->setVertexAttributePointer("aPosition", 2, GL_FLOAT, GL_FALSE, 0, vertices);
//        p->setVertexAttribf("aColor", color.r, color.g, color.b, 0.5);
        p->setUniformMatrixfv("uModelViewProjection", 1, false, _mvp.transpose()._m);
        p->setUniformf("uColor", color.r, color.g, color.b, 0.5);
        //
        ServicesProvider::getInstancePtr()->getRender()->enable(GL_BLEND);
        ServicesProvider::getInstancePtr()->getRender()->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

        //
        //p->setVertexAttribf("aColor", color.r, color.g, color.b, 1.0);
        //ServicesProvider::getInstancePtr()->getRender()->drawArrays(GL_LINE_LOOP, 0, vertexCount);
    } 
}

void box2DRender::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    
}

void box2DRender::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    
}

void box2DRender::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    
}

void box2DRender::DrawTransform(const b2Transform& xf)
{
    
}
