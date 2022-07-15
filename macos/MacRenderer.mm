#include "MacRenderer.h"
#include "gfs/window.hpp"
#include "game2048/game2048.hpp"
#include "MacShaderLibraryBuilder.h"
#include "MacShaderLibrary.h"

@implementation Renderer
{
    Game2048::Game2048* _game;
    MacRenderer* _macRenderer;
}

- (nonnull instancetype) initWithMetalKitView:(nonnull MTKView *) mtkView WithGame:(Game2048::Game2048 *)game WithWindow:(MacWindow*) macWindow WithRenderer:(MacRenderer*) macRenderer
{
    self = [super init];
    
    _game = game;
    macRenderer->SetRenderer(self);
    _macRenderer = macRenderer;
    _macRenderer->SetViewPortPolicy(std::make_unique<gfs::DefaultViewPortPolicy>(_game->GetWindow()));
    
    if(self)
    {
        _macRenderer->Init(mtkView);
    }
    return self;
}

- (void)drawInMTKView:(nonnull MTKView *)view;
{
    _macRenderer->SetMTKView(view);
    _game->Draw();
    _macRenderer->SetMTKView(nullptr);
}

-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
}

@end

void MacRenderer::Draw(gfs::Window* win, std::vector<gfs::Vertex2D>& vertices) {
    MTLRenderPassDescriptor *renderPassDescriptor = mView.currentRenderPassDescriptor;
    if(renderPassDescriptor == nil)
    {
        return;
    }

    id<MTLCommandBuffer> commandBuffer = [mCommandQueue commandBuffer];

    id<MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];

    id<CAMetalDrawable> drawable = mView.currentDrawable;
    
    auto clearColor = GetClearColor();
    mView.clearColor = MTLClearColorMake(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    NSError* pipelineError;
   
    MTLRenderPipelineDescriptor* pipelineDescriptor= [MTLRenderPipelineDescriptor new];
    pipelineDescriptor.label = @"Simple Pipeline";
    pipelineDescriptor.vertexFunction = dynamic_cast<MacShader*>(GetPipeline()->GetVertexShader())->GetShader();
    pipelineDescriptor.fragmentFunction = dynamic_cast<MacShader*>(GetPipeline()->GetFragmentShader())->GetShader();
    pipelineDescriptor.colorAttachments[0].pixelFormat = mView.colorPixelFormat;
    mRenderPipelineState = [mDevice newRenderPipelineStateWithDescriptor: pipelineDescriptor error:&pipelineError];
    
    if(pipelineError != nil) {
        NSLog(@"Pipeline Error");
    }
    
    gfs::ViewPortPolicy* vp = GetViewPortPolicy();
    [commandEncoder setViewport:(MTLViewport){vp->GetBottom(), vp->GetLeft(), vp->GetRight(), vp->GetTop()}];
    
    [commandEncoder setRenderPipelineState:mRenderPipelineState];
    
    if(vertices.size() != 0) {
        [commandEncoder setVertexBytes: vertices.data() length:vertices.size()*sizeof(gfs::Vertex2D) atIndex: 0];
        [commandEncoder setVertexBytes: GetProjection().GetData() length:16*sizeof(float) atIndex: 1];
        [commandEncoder setVertexBytes: GetView().GetData() length:16*sizeof(float) atIndex: 2];

        [commandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:vertices.size()];
    }

    [commandEncoder endEncoding];

    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
}

void MacRenderer::SetRenderer(::Renderer* renderer) {
    mRenderer = renderer;
}

void MacRenderer::Init(MTKView* view) {
    mDevice = view.device;
    mCommandQueue = [mDevice newCommandQueue];
}

void MacRenderer::SetDefaultShaderLibrary(void) noexcept {
    
    MacShaderLibraryBuilder libraryBuilder;
    
    std::string librarySrc =
    "#include <metal_stdlib>\n"
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
    "}\n";
    
    libraryBuilder.AddShaderBlock(librarySrc);
    libraryBuilder.SetMTLDevice(mDevice);
    auto library = libraryBuilder.BuildLibrary();
    SetShaderLibrary(std::move(library));
}

