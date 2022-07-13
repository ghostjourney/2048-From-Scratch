#include "gfs/renderer.hpp"

#include "gfs/window.hpp"

float gfs::DefaultViewPortPolicy::GetTop(void) {
    return mWindow->GetHeight();
}

float gfs::DefaultViewPortPolicy::GetRight(void) {
    return mWindow->GetWidth();
}

void gfs::Renderer::SetProjection(const gfs::Matrix<float, 4, 4>& proj) noexcept {
    mProjection = proj;
    gfs::Transpose<float>(mProjection);
}

void gfs::Renderer::SetView(const gfs::Matrix<float, 4, 4>& view) noexcept {
    mView = view;
    gfs::Transpose<float>(mView);
}
