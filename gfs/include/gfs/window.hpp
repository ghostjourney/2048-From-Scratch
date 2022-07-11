#pragma once

#include <string>

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
    virtual void SetHeightWidth(double height, double width) { mWidth = width; mHeight = height; }

    /**
     * Drawa vertices to screen
     * \param vertices vertices to draw
     */
    virtual void Draw(gfs::Buffer<float, 8>& vertices)=0;

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
        return mWidth;
    }

    /**
     * Gets the cached title
     * \returns cahched title
     */
    inline virtual const std::string& GetTitle(void) const noexcept {
        return mTitle;
    }

    private:

    /// locally cached window title
    std::string mTitle;

    /// locally cached window width
    double mWidth;

    /// locally cached window height
    double mHeight;
};
};
