#pragma once

#include "gfs/matrix.hpp"

#include "gfs/vertex.hpp"

#include "gfs/pipeline.hpp"

namespace gfs {

class ViewPortPolicy {
    public:
        virtual ~ViewPortPolicy() {}
        virtual float GetBottom(void)=0;
        virtual float GetTop(void)=0;
        virtual float GetLeft(void)=0;
        virtual float GetRight(void)=0;
        virtual float GetNear(void)=0;
        virtual float GetFar(void)=0;
};

class Window;
class ShaderLibrary;

class DefaultViewPortPolicy : public ViewPortPolicy {
    public:
        DefaultViewPortPolicy(Window* window) : mWindow{window} {}
        virtual ~DefaultViewPortPolicy() {}
    
        float GetBottom(void) override { return 0.0f; }
        float GetTop(void) override;
        float GetLeft(void) override { return 0.0f; }
        float GetRight(void) override;
        float GetNear(void) override { return 0.0f; }
        float GetFar(void) override { return 100.0f; }
    
    private:
        /// non owned pointer
        Window* mWindow;
};

class Renderer {
    public:
        Renderer(void);
        virtual ~Renderer(void);
        Renderer(const Renderer&)=delete;
        Renderer(const Renderer&&)=delete;
        Renderer&& operator=(const Renderer&)=delete;
        Renderer&& operator=(const Renderer&&)=delete;
    
        void SetView(const gfs::Matrix<float, 4, 4>& view) noexcept;
    
        gfs::Matrix<float, 4, 4>& GetView(void) noexcept {
            return mView;
        }

        void SetProjection(const gfs::Matrix<float, 4, 4>& proj) noexcept;
        
        gfs::Matrix<float, 4, 4>& GetProjection(void) noexcept {
            return mProjection;
        }

        virtual void Draw(gfs::Window* win, std::vector<Vertex2D>& vertices)=0;
    
        void SetViewPortPolicy(std::unique_ptr<ViewPortPolicy> vp) {
            mViewPortPolicy = std::move(vp);
        }
    
        ViewPortPolicy* GetViewPortPolicy(void) {
            return mViewPortPolicy.get();
        }
    
        void SetClearColor(float r, float g, float b, float a) {
            mClearColor[0] = r;
            mClearColor[1] = g;
            mClearColor[2] = b;
            mClearColor[3] = a;
        }
    
        void SetClearColor(std::array<float, 4>& color) {
            mClearColor = color;
        }
    
        std::array<float, 4>& GetClearColor(void) noexcept {
            return mClearColor;
        }

        virtual std::unique_ptr<Pipeline> CreatePipeline(void) noexcept;

        virtual void SetDefaultShaderLibrary(void) noexcept { }

        virtual void SetShaderLibrary(std::unique_ptr<ShaderLibrary> library);

        virtual ShaderLibrary* GetShaderLibrary(void);
    
        virtual void SetPipeline(std::unique_ptr<gfs::Pipeline> pipeline);
    
        virtual Pipeline* GetPipeline(void);

    private:
        /// matrix projection being used
        gfs::Matrix<float, 4, 4> mProjection;
   
        /// matrix view being used
        gfs::Matrix<float, 4, 4> mView;
   
        /// parameters being used for setting the view port
        std::unique_ptr<ViewPortPolicy> mViewPortPolicy;
    
        /// clear color
        std::array<float, 4> mClearColor;
    
        std::unique_ptr<ShaderLibrary> mShaderLibrary;
    
        std::unique_ptr<Pipeline> mPipeline;
};
};
