#pragma once

#include "window.hpp"

@class Renderer;

@class AppDelegate;


class MacWindow : public Window {
    public:
    void SetAppDelegate(AppDelegate *delegate);
    void SetRenderer(Renderer *renderer);
    bool Init(void) override;
    void SetTitle(std::string title) override;
    private:

    /// provided. Not owned
    AppDelegate* mAppDelegate;

    /// provided. Not owned
    Renderer* mRenderer;
};

