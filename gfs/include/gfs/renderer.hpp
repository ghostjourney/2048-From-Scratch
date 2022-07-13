#pragma once

#include "gfs/matrix.hpp"

#include "gfs/vertex.hpp"

namespace gfs {

class Window;
class Renderer {
    public:
        Renderer()=default;
        virtual ~Renderer() {}
        Renderer(const Renderer&)=delete;
        Renderer(const Renderer&&)=delete;
        Renderer&& operator=(const Renderer&)=delete;
        Renderer&& operator=(const Renderer&&)=delete;

        void SetProjection(const gfs::Matrix<float, 4, 4>& proj);

        virtual void Draw(gfs::Window* win, std::vector<Vertex2D>& vertices)=0;
    private:
        /// the projection matrix to use
        gfs::Matrix<float, 4, 4> mProjection;
};
};
