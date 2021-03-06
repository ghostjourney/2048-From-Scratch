#pragma once

#include <string>

#include "gfs/renderer.hpp"

#include "gfs/buffer.hpp"

namespace gfs {

/**
 * Abstract Window handler
 *
 * Holds and controls the window for the game. Platform specific subclasses provided to application
 * based on this class
 */
class Window {
    public:
    Window()=default;
    /** window should never be copied */
    Window(const Window&)=delete;

    /** window should never be copied */
    Window& operator=(const Window&)=delete;
    
    virtual ~Window() {}

    /**
     * First call after the constructor. Initializes the Window. 
     * \returns true if successful. Otherwise false.
     */
    virtual bool Init(void)=0;
    
    /**
     * Sets the window title. Should be override to set the underlying window title
     * \param title new title
     */ 
    virtual void SetTitle(std::string title);
   
    /**
     * Sets the height and width of the window. Should be override with platform specific handling.
     * \param height new height
     * \param width new width
     */
    virtual void SetHeightWidth(double height, double width) {
        mWidth = width;
        mHeight = height;
        
    }

    /**
     * Gets the cached width
     * \returns cahched width
     */
    inline virtual double GetWidth(void) const noexcept {
        return mWidth;
    }

    /**
     * Gets the cached height
     * \returns cahched height
     */
    inline virtual double GetHeight(void) const noexcept {
        return mHeight;
    }

    /**
     * Gets the cached title
     * \returns cahched title
     */
    inline virtual const std::string& GetTitle(void) const noexcept {
        return mTitle;
    }

    /**
     * Sets the platform specific renderer for this window
     * \param renderer platform specific renderer
     */
    void SetRenderer(std::unique_ptr<Renderer> renderer) noexcept {
        mRenderer = std::move(renderer);
    }
    
    
    /**
     * Gets the platform specific renderer for this window
     * \returns the platform specific renderer.
     */
    Renderer* GetRenderer(void) const noexcept {
        return mRenderer.get();
    }

    private:

    /// renderer
    std::unique_ptr<Renderer> mRenderer;

    /// locally cached window title
    std::string mTitle;

    /// locally cached window width
    double mWidth;

    /// locally cached window height
    double mHeight;
};
};
