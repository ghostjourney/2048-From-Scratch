#include "MacWindow.h"

#include <AppKit/AppKit.h>

#include "AppDelegate.h"

void MacWindow::SetHeightWidth(double height, double width) {
    Window::SetHeightWidth(height, width);
    
    NSRect frame = [[mAppDelegate window] frame];
    frame.size = NSMakeSize(width, height);
    
    [[mAppDelegate window] setFrame: frame display: YES animate: false];
    
}

bool MacWindow::MacWindow::Init(void) {
    return true;
}

void MacWindow::SetAppDelegate(AppDelegate *delegate) {
    mAppDelegate = delegate;
}

void MacWindow::SetTitle(std::string title) {
    Window::SetTitle(title);
    [mAppDelegate window].title = [[NSString alloc] initWithUTF8String:title.c_str()];
}
