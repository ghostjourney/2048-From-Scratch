#pragma once

namespace gfs {

class Shader;

/**
 * Holds the shaders used by the Program.
 *
 * Individual Platforms take this to setup platform thier pipeline but
 * may not be directly tied to it
 */
class Pipeline {
    public:
        Pipeline(void)=default;
        Pipeline(const Pipeline&)=delete;

        Pipeline& operator=(const Pipeline&)=delete;

        virtual ~Pipeline() {}

        virtual void SetVertexShader(Shader* v_shader) noexcept {
            mVShader = v_shader;
        }

        virtual Shader* GetVertexShader(void) noexcept {
            return mVShader;
        }

        virtual void SetFragmentShader(Shader* f_shader) noexcept {
            mFShader = f_shader;
        }

        virtual Shader* GetFragmentShader(void) noexcept {
            return mFShader;
        }
    private:
        /// not owned. Should be tied to ShaderLibrary which is program length
        Shader *mVShader;

        /// not owned. Should be tied to ShaderLibrary which is program length
        Shader *mFShader;
};

};
