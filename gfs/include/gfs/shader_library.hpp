#pragma once

#include <string>

namespace gfs {

class Shader;

/**
 * holds all shaders and programs
 *
 * do to the natures of opengl and metal, the shader storage and use is platform specific. 
 * Therefore platform specific versions of this class must be created.
 *
 */
class ShaderLibrary {

    public:

    /**
     * retrieves a shader object
     * 
     * \param name name of shader
     */
    virtual Shader* GetShader(std::string name)=0;

    private:

};
}
