#pragma once

#include <string>

namespace gfs {

class Window {
    public:
    virtual bool Init(void)=0;
    virtual void SetTitle(std::string title);
    
    virtual void SetHeightWidth(double height, double width) { mWidth = width; mHeight = height; }
    
    private:
    std::string mTitle;
    double mWidth;
    double mHeight;
};
};
