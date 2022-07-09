#pragma once

#include <string>

class Window {
    public:
    virtual bool Init(void)=0;
    virtual void SetTitle(std::string title);

    private:
        std::string mTitle;
};
