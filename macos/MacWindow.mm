#include "MacWindow.h"

#include <Appkit/AppKit.h>
#include "AppDelegate.h"
#include "Renderer.h"

void MacWindow::SetRenderer(Renderer* renderer) {
    mRenderer = renderer;
}

void MacWindow::SetHeightWidth(double height, double width) {
    Window::SetHeightWidth(height, width);
    
    [[mAppDelegate window] setContentSize:NSMakeSize(width, height)];
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
