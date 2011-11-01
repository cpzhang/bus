//
//  GLView.m
//  angry_bus
//
//  Created by suning on 11-10-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "GLView.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@implementation GLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) 
    {
        // Initialization code
        CAEAGLLayer* e = (CAEAGLLayer*)super.layer;
        e.opaque = YES;
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        _context = [[EAGLContext alloc] initWithAPI:api];
        if (!_context) 
        {
            api = kEAGLRenderingAPIOpenGLES1;
            [[EAGLContext alloc] initWithAPI:api];
        }
        
        if (!_context || ![EAGLContext setCurrentContext:_context]) 
	{
            [self release];
            return nil;
        }
        _boot.initSingletons();
        //
        if (api == kEAGLRenderingAPIOpenGLES1)
        {
            NSLog(@"Applying OPenGLES1");
            _boot.applyRender(eRender_ES1);
        }
        else
        {
            NSLog(@"Applying OPenGLES2");
            _boot.applyRender(eRender_ES2);
        }
        if (!_boot.create()) 
        {
            return nil;
        }
        _boot.setViewPort(CGRectGetWidth(frame), CGRectGetHeight(frame));
        [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable: e];
        [[CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)] addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    return self;
}

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (void) drawView: (CADisplayLink*) displayLink
{
    // update
    static float s_last_time_stamp = displayLink.timestamp;
    float elapsed_seconds = displayLink.timestamp - s_last_time_stamp;
    s_last_time_stamp = displayLink.timestamp;

    _boot.run(elapsed_seconds);

    // [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)dealloc
{
    _boot.destroy();
    if ([EAGLContext currentContext] == _context) 
    {
        [EAGLContext setCurrentContext:nil];
    }
    [_context release];
    [super dealloc];
}

@end
