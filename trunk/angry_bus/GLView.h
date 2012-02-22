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
- (void) memoryWarning;
@end
