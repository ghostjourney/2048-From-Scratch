#include "MacRenderer.h"

#include "gfs/window.hpp"

#include "game2048/game2048.hpp"

@implementation Renderer
{
    id<MTLDevice> _device;
    id<MTLCommandQueue> _commandQueue;
    id<MTLLibrary> _library;
    
    id<MTLRenderPipelineState> _renderPipelineState;
    
    id<MTLFunction> _vs;
    id<MTLFunction> _fs;
    
    Game2048::Game2048* _game;
}

- (nonnull instancetype) initWithMetalKitView:(nonnull MTKView *) mtkView WithGame:(Game2048::Game2048 *)game WithWindow:(MacWindow*) macWindow WithRenderer:(MacRenderer*) macRenderer
{
    self = [super init];
    
    _game = game;
    macRenderer->SetRenderer(self);
    
    if(self)
    {
        _device = mtkView.device;
        _commandQueue = [_device newCommandQueue];
        
       MTLCompileOptions* compileOptions = [MTLCompileOptions new];
        compileOptions.languageVersion = MTLLanguageVersion2_4;

        NSError* compileError;

        _library = [_device newLibraryWithSource:
            @"#include <metal_stdlib>\n"
            "using namespace metal;\n"
            "struct VertexBuffer {\n"
            "   float2 position;\n"
            "   float4 color;\n"
            "   float2 tex;\n"
            "};\n"
            "struct v2f {\n"
            "   float4 position [[position]];\n"
            "   float4 color;\n"
            "};\n"
            "v2f vertex v_simple(\n"
            "    device const VertexBuffer* in   [[buffer(0)]],\n"
            "    device const float4x4*     p [[buffer(1)]],\n"
            "    device const float4x4*     v [[buffer(2)]],\n"
            "    uint                vid    [[vertex_id]])\n"
            "{\n"
            "    v2f o;\n"
            "    o.position = (*p) * (*v) * float4(in[vid].position.xy, 0.0, 1.0);\n"
            "    o.position = float4(o.position.xy, o.position.z*-1.0f, 1.0);\n"
            "    o.color = in[vid].color.xyzw;\n"
            "    return o;\n"
            "}\n"
            "fragment float4 f_simple(\n"
            "   v2f in [[stage_in]])\n"
            "{\n"
            "    return in.color.xyzw;\n"
            "}\n"
            options:compileOptions error:&compileError];

        if(!_library) {
            NSLog(@"Error Creating MTLLibrary");
        }

        _vs = [_library newFunctionWithName:@"v_simple"];
        _fs = [_library newFunctionWithName:@"f_simple"];
    }
    return self;
}

#include <simd/simd.h>

struct Test {
    simd_float2 pos;
    simd_float4 color;
};

- (void)drawInMTKView:(nonnull MTKView *)view;
{
    _game->Draw();
    
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
    if(renderPassDescriptor == nil)
    {
        return;
    }

    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];

    id<MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

    id<CAMetalDrawable> drawable = view.currentDrawable;
   
    //MTLRenderPassColorAttachmentDescriptor* cd = renderPassDescriptor.colorAttachments[0];
    //cd.texture = drawable.texture;
    //cd.loadAction = MTLLoadActionClear;
    //cd.clearColor = MTLClearColorMake(0.0, 0.0, 1.0, 1.0);
    //cd.storeAction = MTLStoreActionStore;
   
    view.clearColor = MTLClearColorMake(0.0,0.0,1.0, 1.0);

    NSError* pipelineError;
   
    MTLRenderPipelineDescriptor* pipelineDescriptor= [MTLRenderPipelineDescriptor new];
    pipelineDescriptor.label = @"Simple Pipeline";
    pipelineDescriptor.vertexFunction = _vs;
    pipelineDescriptor.fragmentFunction = _fs;
    pipelineDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat;
    _renderPipelineState = [_device newRenderPipelineStateWithDescriptor: pipelineDescriptor error:&pipelineError];
    
    if(pipelineError != nil) {
        NSLog(@"Pipeline Error");
    }
    
    
    auto w = view.frame.size.width;
    auto h = view.frame.size.height;
    
    
    auto proj = gfs::ProjectionMatrix<float>(0.0f, view.frame.size.width, 0.0f, view.frame.size.height, 0.0f, 100.0f);
    gfs::Transpose<float>(proj);
    //auto viewMatrix = gfs::ScaleMatrix(1.0f,1.0f, -1.0f);
    auto viewMatrix = gfs::CreateIdentity<float, 4>(1.0f);
    gfs::Transpose<float>(viewMatrix);
    [commandEncoder setViewport:(MTLViewport){0.0, 0.0, view.frame.size.width, view.frame.size.height, 0.0, 1.0}];
    
    [commandEncoder setRenderPipelineState:_renderPipelineState];
    
    
    
    auto vertices = _game->Draw();
    
    if(vertices->size() != 0) {
        [commandEncoder setVertexBytes: vertices->data() length:vertices->size()*sizeof(gfs::Vertex2D) atIndex: 0];
        [commandEncoder setVertexBytes: proj.GetData() length:16*sizeof(float) atIndex: 1];
        [commandEncoder setVertexBytes: viewMatrix.GetData() length:16*sizeof(float) atIndex: 2];

        [commandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:vertices->size()];
    }

    [commandEncoder endEncoding];

    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
}

-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
}

@end

void MacRenderer::Draw(gfs::Window* win, std::vector<gfs::Vertex2D>& vertices) {
    auto windowWidth = win->GetWidth();
    auto windowHeight = win->GetHeight();
    
}

void MacRenderer::SetRenderer(::Renderer* renderer) {
    mRenderer = renderer;
}
