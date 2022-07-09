#import "MetalKit/MetalKit.h"

namespace Game2048 {
class Game2048;
};

class MacWindow;


@interface Renderer : NSObject<MTKViewDelegate>
- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)mtkView WithGame:(Game2048::Game2048*) game WithWindow:(MacWindow *) macWindow;
@end
