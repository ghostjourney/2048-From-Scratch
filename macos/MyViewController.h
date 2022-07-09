
#import <AppKit/AppKit.h>

#import <MetalKit/MetalKit.h>

#include "game.hpp"


@interface MyViewController : NSViewController

- (instancetype) initWithGame: (Game2048::Game2048*_Nullable) game;


@end
