#pragma once

#include "window.hpp"

@class Renderer;

@class AppDelegate;


class MacWindow : public gfs::Window {
    public:
    
    bool Init(void) override;
    void SetTitle(std::string title) override;
    
    void SetHeightWidth(double height, double width) override;
   
    // MacWindow specific code
    
    void SetAppDelegate(AppDelegate *delegate);
    
    void SetRenderer(Renderer *renderer);
   
    private:

    /// provided. Not owned
    AppDelegate* mAppDelegate;

    /// provided. Not owned
    Renderer* mRenderer;
};

