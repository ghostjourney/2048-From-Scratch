#include "gfs/renderer.hpp"

void gfs::Renderer::SetProjection(const gfs::Matrix<float, 4, 4>& proj) noexcept {
    mProjection = proj;
    gfs::Transpose<float>(mProjection);
}
