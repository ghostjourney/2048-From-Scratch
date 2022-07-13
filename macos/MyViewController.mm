#import "MyViewController.h"

#include "MacRenderer.h"

@implementation MyViewController
{
    MTKView* _view;
    
    Renderer* _renderer;
    
    MacRenderer* _macRenderer;
    
    Game2048::Game2048* _game;
    MacWindow* _macWindow;
}

- (instancetype) initWithGame:(Game2048::Game2048 *_Nullable)game WithWindow:(MacWindow *) macWindow{
   
    self = [super initWithNibName:nil bundle:nil];
    _game = game;
    _macWindow = macWindow;
    
    auto macRenderer = std::make_unique<MacRenderer>();
    _macWindow->SetRenderer(std::move(macRenderer));
    
    
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
    
    _game->GetWindow()->SetRenderer(std::make_unique<MacRenderer>());
    auto r = dynamic_cast<MacRenderer*>(_game->GetWindow()->GetRenderer());
    

    _renderer = [[Renderer alloc] initWithMetalKitView:_view WithGame:_game WithWindow: _macWindow WithRenderer: r];

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

