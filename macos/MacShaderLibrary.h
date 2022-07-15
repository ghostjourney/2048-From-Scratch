#pragma once

#include "gfs/shader_library.hpp"

#include "MacShader.h"

#include <unordered_map>

class MacShaderLibraryBuilder;
@protocol MTLLibrary;

class MacShaderLibrary : public gfs::ShaderLibrary {
    public:
        gfs::Shader* GetShader(std::string name) override;
        MacShader* GetMacShader(std::string name);
    private:
        id<MTLLibrary> mLibrary;
        friend MacShaderLibraryBuilder;
        std::unordered_map<std::string, std::unique_ptr<MacShader>> mShaders;
};
