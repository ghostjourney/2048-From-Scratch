#pragma once

#include <string>

#include "gfs/buffer.hpp"

namespace gfs {

class Window {
    public:
    virtual bool Init(void)=0;
    virtual void SetTitle(std::string title);
    
    virtual void SetHeightWidth(double height, double width) { mWidth = width; mHeight = height; }

    virtual void Draw(gfs::Buffer<float, 2>& vertices)=0;

    private:
    std::string mTitle;
    double mWidth;
    double mHeight;
};
};
