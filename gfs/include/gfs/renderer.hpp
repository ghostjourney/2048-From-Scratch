#pragma once

#include "gfs/matrix.hpp"

#include "gfs/vertex.hpp"

namespace gfs {

struct ViewPort {
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;
    
    ViewPort(float left, float right, float top, float bottom, float near, float far) {
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;
        this->near = near;
        this->far = far;
    }
};

class Window;
class Renderer {
    public:
        Renderer() {
            mClearColor[0] = 1.0f;
            mClearColor[1] = 1.0f;
            mClearColor[2] = 1.0f;
            mClearColor[3] = 1.0f;
        }
        virtual ~Renderer() {}
        Renderer(const Renderer&)=delete;
        Renderer(const Renderer&&)=delete;
        Renderer&& operator=(const Renderer&)=delete;
        Renderer&& operator=(const Renderer&&)=delete;
    
        void SetView(const gfs::Matrix<float, 4, 4>& view) noexcept {
            mView = view;
        }
    
        gfs::Matrix<float, 4, 4>& GetView(void) noexcept {
            return mView;
        }

        void SetProjection(const gfs::Matrix<float, 4, 4>& proj) noexcept;
        
        gfs::Matrix<float, 4, 4>& GetProjection(void) noexcept {
            return mProjection;
        }

        virtual void Draw(gfs::Window* win, std::vector<Vertex2D>& vertices)=0;
    
        void setViewPortParameters(std::unique_ptr<ViewPort> vp) {
            mViewPortParameters = std::move(vp);
        }
    
        ViewPort* GetViewPortParameters(void) {
            return mViewPortParameters.get();
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
    private:
        /// the projection matrix to use
        gfs::Matrix<float, 4, 4> mProjection;
    
        gfs::Matrix<float, 4, 4> mView;
    
        std::unique_ptr<ViewPort> mViewPortParameters;
        std::array<float, 4> mClearColor;
    
};
};
