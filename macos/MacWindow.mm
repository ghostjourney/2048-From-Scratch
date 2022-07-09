#include "MacWindow.h"

bool MacWindow::MacWindow::Init(void) {
}

void MacWindow::SetAppDelegate(AppDelegate *delegate) {
    mAppDelegate = delegate;
}

void MacWindow::SetTitle(std::string title) {
    Window::SetTitle(title);
    [mAppDelegate window].title = [[NSString alloc] initWithUTF8String:title.c_str()];
}
