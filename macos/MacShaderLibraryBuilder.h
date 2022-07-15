#pragma once

#include "gfs/shader_library_builder.hpp"
#include "MacShaderLibrary.h"

#include <vector>
#include <utility>

#include "MetalKit/MetalKit.h"

class MacShaderLibraryBuilder : public gfs::ShaderLibraryBuilder {
    public:
        void AddShader(std::string& name, std::string& shader_src) override;

        std::unique_ptr<gfs::ShaderLibrary> BuildLibrary(void) override;
        std::unique_ptr<MacShaderLibrary> BuildMacShaderLibrary(void);


        void AddShaderBlock(std::string& shader_src) override;

        void SetMTLDevice(id<MTLDevice> device);
    private:
        std::vector<std::pair<std::string, std::string>> mShadersSrcs;
        id<MTLDevice> mDevice;
};
