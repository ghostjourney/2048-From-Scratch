#import "Renderer.h"

#include "game2048/game2048.hpp"

#include "MacWindow.h"

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

- (nonnull instancetype) initWithMetalKitView:(nonnull MTKView *) mtkView WithGame:(Game2048::Game2048 *)game WithWindow:(MacWindow*) macWindow
{
    self = [super init];
    
    _game = game;
    
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
            "    device const VertexBuffer* in     [[buffer(0)]],\n"
            "    uint                vid    [[vertex_id]])\n"
            "{\n"
            "    v2f o;\n"
            "    o.position = float4(in[vid].position.xy, 0.0, 1.0);\n"
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
    
    [commandEncoder setViewport:(MTLViewport){0.0, 0.0, view.frame.size.width, view.frame.size.height, 0.0, 1.0}];
    
    auto matrix = gfs::CreateIdentity<float, 4>(1.0f);
    
    [commandEncoder setRenderPipelineState:_renderPipelineState];

    auto vertices = _game->Draw();

    if(vertices->size() != 0) {
        [commandEncoder setVertexBytes: vertices->data() length:vertices->size()*sizeof(gfs::Vertex2D) atIndex: 0];

        //[commandEncoder setVertexBytes: matrix.GetData() length: matrix.GetColumns() * matrix.GetRows() * sizeof(float) atIndex: 1];

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


