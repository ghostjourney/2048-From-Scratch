#pragma once

#include <string>
#include <vector>

#include "gfs/shader_library.hpp"

namespace gfs {

class ShaderLibraryBuilder {
    public:
        /**
         * Adds the shader src with the given name to the library.
         * For consistency across platforms, the shader name should be the
         * same as the function name if the underlying platform supports
         * different names.
         * \param name name of the shader
         * \param shader_src shader_src
         */
        virtual void AddShader(std::string& name, std::string& shader_src)=0;

        /**
         * Builds and returns the ShaderLibrary. Returns empty unique ptr
         * if it fails
         * \returns the new shader library, or null if failure
         */
        virtual std::unique_ptr<ShaderLibrary> BuildLibrary(void)=0;

        /**
         * Adds a block of shader_src that may contain many shaders if the
         * underlying platform allows it
         * \param shader_src block of shader_src
         */
        virtual void AddShaderBlock(std::string& shader_src)=0;
};
};
