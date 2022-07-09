//
//  AppDelegate.m
//
//

#import "AppDelegate.h"

#import "MyViewController.h"

#include "MacWindow.h"

#include "game.hpp"




@implementation AppDelegate {
    std::unique_ptr<Game2048::Game2048> _game;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    _game = std::make_unique<Game2048::Game2048>();
    auto window = std::make_unique<MacWindow>();
    window->SetAppDelegate(self);
    _game->SetWindow(std::move(window));
    _window.contentViewController = [[MyViewController alloc] init];
    
    _game->Init();
}


- (void)applicationWillTerminate:(NSNotification *)aNotification
{
    // Insert code here to tear down your application
    
    _game->Terminate();
}


- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app
{
    _game->SaveState();
    return YES;
}


@end
