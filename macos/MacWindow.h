#pragma once

#include "window.hpp"

#import <Appkit/AppKit.h>
#import "AppDelegate.h"

class MacWindow : public Window {
    public:
    void SetAppDelegate(AppDelegate *delegate);
    bool Init(void) override;
    void SetTitle(std::string title) override;
    private:
    AppDelegate* mAppDelegate;
};

