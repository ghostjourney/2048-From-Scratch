
#import <AppKit/AppKit.h>

#import <MetalKit/MetalKit.h>

#include "game2048/game2048.hpp"

#include "MacWindow.h"


@interface MyViewController : NSViewController

- (instancetype) initWithGame: (Game2048::Game2048*_Nullable) game WithWindow: (MacWindow *) macWindow;


@end
