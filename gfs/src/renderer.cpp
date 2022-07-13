#include "gfs/renderer.hpp"

void gfs::Renderer::SetProjection(const gfs::Matrix<float, 4, 4>& proj) {
    mProjection = proj;
}
