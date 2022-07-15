#pragma once
#include "gfs/shader.hpp"

@protocol MTLFunction;

class MacShader : public gfs::Shader {
    public:
        MacShader(id<MTLFunction> shader);
        id<MTLFunction> GetShader(void);

    private:
        id<MTLFunction> mShader;
};
