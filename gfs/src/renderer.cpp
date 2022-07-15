#include "gfs/renderer.hpp"

#include "gfs/window.hpp"

#include "gfs/shader_library.hpp"
#include "gfs/pipeline.hpp"

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

gfs::Renderer::Renderer(void) {
    mClearColor[0] = 1.0f;
    mClearColor[1] = 1.0f;
    mClearColor[2] = 1.0f;
    mClearColor[3] = 1.0f;
}

gfs::Renderer::~Renderer(void) {}

std::unique_ptr<gfs::Pipeline> gfs::Renderer::CreatePipeline(void) noexcept {
    return std::make_unique<gfs::Pipeline>();
}


void gfs::Renderer::SetShaderLibrary(std::unique_ptr<gfs::ShaderLibrary> library) {
    mShaderLibrary = std::move(library);
}

gfs::ShaderLibrary* gfs::Renderer::GetShaderLibrary() {
    return mShaderLibrary.get();
}

void gfs::Renderer::SetPipeline(std::unique_ptr<gfs::Pipeline> pipeline) {
    mPipeline = std::move(pipeline);
}
    
gfs::Pipeline* gfs::Renderer::GetPipeline(void) {
    return mPipeline.get();
}
