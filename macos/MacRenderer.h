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
- (nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)mtkView WithGame:(Game2048::Game2048*) game WithWindow:(MacWindow *) macWindow WithRenderer:(MacRenderer*) macRenderer;
@end

class MacRenderer : public gfs::Renderer {
    public:
    
        void Draw(gfs::Window* win, std::vector<gfs::Vertex2D>& vertices) override;
    
        void SetRenderer(::Renderer* renderer);
    
        void SetMTKView(MTKView* view) { mView = view; }
    
        void Init(MTKView* view);

    private:
        ::Renderer *mRenderer;
    
        MTKView* mView;
    
        id<MTLDevice> mDevice;
        id<MTLCommandQueue> mCommandQueue;
    
        std::unique_ptr<MacShaderLibrary> mLibrary;
    
        id<MTLRenderPipelineState> mRenderPipelineState;
    
        MacShader* mVS;
        MacShader* mFS;
};
