#pragma once

#import "MetalKit/MetalKit.h"

#include "gfs/renderer.hpp"

#include "MacShaderLibrary.h"

class MacShader;

namespace Game2048 {
class Game2048;
};

class MacWindow;
class MacRenderer;

@interface Renderer : NSObject<MTKViewDelegate>
- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)mtkView WithGame:(Game2048::Game2048* _Nullable) game WithWindow:(MacWindow * _Nullable) macWindow WithRenderer:(MacRenderer* _Nullable) macRenderer;
@end

class MacRenderer : public gfs::Renderer {
    public:
    
        void Draw(gfs::Window* _Nullable win, std::vector<gfs::Vertex2D>& vertices) override;
    
        void SetRenderer(::Renderer* _Nullable renderer);
    
        void SetMTKView(MTKView* _Nullable view) { mView = view; }
    
        void Init(MTKView* _Nullable view);

        void SetDefaultShaderLibrary(void) noexcept override;
    
    private:
        ::Renderer* _Nullable mRenderer;
    
        MTKView* _Nullable mView;
    
        id<MTLDevice> _Nullable mDevice;
        id<MTLCommandQueue> _Nullable mCommandQueue;
    
        id<MTLRenderPipelineState> _Nullable mRenderPipelineState;
};
