#import "MyViewController.h"

#import "Renderer.h"

@implementation MyViewController
{
    MTKView* _view;
    
    Renderer* _renderer;
    
    Game2048::Game2048* _game;
}

- (instancetype) initWithGame:(Game2048::Game2048 *_Nullable)game {
   
    self = [super initWithNibName:nil bundle:nil];
    _game = game;
    
    return self;
}

- (void) loadView
{
    self.view = [[MTKView alloc] initWithFrame: NSMakeRect(0.0, 0.0, 1920.0, 1080.0)];
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _view = (MTKView *) self.view;
    
    _view.device = MTLCreateSystemDefaultDevice();
    

    _renderer = [[Renderer alloc] initWithMetalKitView:_view WithGame:_game];
    

    if(!_renderer)
    {
        NSLog(@"Renderer initialization failed");
        return;
    }

    // Initialize the renderer with the view size.
    [_renderer mtkView:_view drawableSizeWillChange:_view.drawableSize];

    
    _view.delegate = _renderer;
    
}

@end

