//
//  GLView.h
//  angry_bus
//
//  Created by suning on 11-10-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import "IRender.h"
#import "bootstrapper.h"
@interface GLView : UIView
{
    // protected
    EAGLContext*    _context;
    //
    IRender*        _render;
    //
    BootStrapper    _boot;
}
    // public
- (void) drawView: (CADisplayLink*) displayLink;

@end
