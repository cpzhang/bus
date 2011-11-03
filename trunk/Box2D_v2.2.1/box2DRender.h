//
//  box2DRender.h
//  angry_bus
//
//  Created by suning on 11-11-2.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef _Box2DRender_
#define _Box2DRender_
#include <Box2D/Common/b2Draw.h>
#include "Matrix4.h"
class box2DRender : public b2Draw
{
public:
    box2DRender();
    ~box2DRender();
    
    /// Draw a closed polygon provided in CCW order.
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    
	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    
	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	
	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	
	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    
	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf);
    
private:
    Matrix4 _mvp;
};
#endif