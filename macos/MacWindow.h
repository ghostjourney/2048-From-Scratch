#pragma once

#include "gfs/window.hpp"

@class Renderer;

@class AppDelegate;

class MacWindow : public gfs::Window {
    public:
    
    bool Init(void) override;

    void SetTitle(std::string title) override;

    void SetHeightWidth(double height, double width) override;
    
    void SetAppDelegate(AppDelegate *delegate);
    
    private:

    /// provided. Not owned
    AppDelegate* mAppDelegate;
};
