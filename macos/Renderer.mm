#import "Renderer.h"

#include "game.hpp"

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
            "vertex float4 v_simple(\n"
            "    constant float4* in  [[buffer(0)]],\n"
            "    uint             vid [[vertex_id]])\n"
            "{\n"
            "    return in[vid];\n"
            "}\n"
            "fragment float4 f_simple(\n"
            "    float4 in [[stage_in]])\n"
            "{\n"
            "    return float4(1, 0, 0, 1);\n"
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
    
    if(pipelineError == nil) {
        NSLog(@"Pipeline Error");
    }
    
    [commandEncoder setViewport:(MTLViewport){0.0, 0.0, view.frame.size.width, view.frame.size.height, 0.0, 1.0}];
    
    
    
    [commandEncoder setRenderPipelineState:_renderPipelineState];
    [commandEncoder setVertexBytes:(vector_float4[]){
        { 0, 0, 0, 1},
        {-1, 1, 0, 1},
        { 1, 1, 0, 1}
    } length:3 * sizeof(vector_float4) atIndex: 0];
    
    [commandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

    [commandEncoder endEncoding];

    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
}

-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
}

@end


