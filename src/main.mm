#include <iostream>
#include <string>
#include <sstream>

#define GLFW_INCLUDE_NONE 1
#include "GLFW/glfw3.h"

#define GLFW_EXPOSE_NATIVE_COCOA 1
#include "GLFW/glfw3native.h"

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

#include <simd/simd.h>

#include "Matrix.hpp"

void window_refresh_callback(GLFWwindow* window) {

}

void window_close_callback(GLFWwindow* window) {

}


class Logger {
    public:
    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    virtual void Log(Level level, std::string message)=0;

    virtual void LogFatal(std::string message)=0;

    virtual void LogError(std::string message)=0;

    std::string LevelToString(const Level level) {
        switch(level) {
            case Level::TRACE:
                return "TRACE";
            case Level::DEBUG:
                return "DEBUG";
            case Level::INFO:
                return "INFO";
            case Level::WARN:
                return "WARN";
            case Level::ERROR:
                return "ERROR";
            case Level::FATAL:
                return "FATAL";
        }
    }
};

class ConsoleLogger : public Logger {
    public:
    void Log(Logger::Level level, std::string message) override {
        std::cout << Logger::LevelToString(level) << ": " << message << std::endl;
    }

    void LogFatal(std::string message) override {
        Log(Logger::Level::FATAL, message);
    }

    void LogError(std::string message) override {
        Log(Logger::Level::ERROR, message);
    }
};

class Window {
    public:
        Window(Logger* logger) : mLogger{logger} {};

        Window(const Window&)=delete;
        Window(const Window&&)=delete;
        Window& operator=(const Window& window)=delete;
        Window& operator=(const Window&& window)=delete;

        bool Init(int windowWidth, int windowHeight) noexcept;

        virtual void Draw(void) noexcept;

        void SetTitle(std::string title) noexcept {
            mTitle = title;
            if(mWindow) {
                glfwSetWindowTitle(mWindow, mTitle.c_str());
            }
        }

        bool ShouldClose(void) noexcept {
            return glfwWindowShouldClose(mWindow);
        }

        ~Window();
    private:
        id<MTLDevice> mDevice;
        id<MTLCommandQueue> mCommandQueue;
        id<MTLRenderPipelineState> mRenderPipelineState;
        id<MTLLibrary> mLibrary;
        id<MTLFunction> mVS;
        id<MTLFunction> mFS;
        CAMetalLayer* mLayer;
        MTLRenderPipelineDescriptor* mRenderPipelineDescriptor;
        

        bool mWasInitialized{false};

        /// application logger. Provided. Not Owned.
        Logger* mLogger;

        GLFWwindow* mWindow{nullptr};

        NSWindow* mNSWindow;

        std::string mTitle{"Main"};
};

bool Window::Init(int windowWidth=1920, int windowHeight=1080) noexcept {
    mDevice = MTLCreateSystemDefaultDevice();

    if(!mDevice) {
        mLogger->LogFatal("Could not Create MTL System Device");
        return false;
    }

    if(!glfwInit()) {
        mLogger->LogFatal("Could not initialize GLFW");
        return false;
    }
    mWasInitialized = true;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    mWindow = glfwCreateWindow(windowWidth, windowHeight, mTitle.c_str(), nullptr, nullptr);

    if(!mWindow) {
        mLogger->LogFatal("Could not create GLFW Window");
        return false;
    }

    glfwSetWindowRefreshCallback(mWindow, window_refresh_callback);

    mNSWindow = glfwGetCocoaWindow(mWindow);
    mLayer = [CAMetalLayer layer];
    if(!mLayer) {
        mLogger->LogFatal("CAMetalLayer failed");
        return -1;
    }

    mLayer.device = mDevice;
    mLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    mNSWindow.contentView.layer = mLayer;
    mNSWindow.contentView.wantsLayer = YES;

    MTLCompileOptions* compileOptions = [MTLCompileOptions new];
    compileOptions.languageVersion = MTLLanguageVersion2_4;

    NSError* compileError;

    mLibrary = [mDevice newLibraryWithSource:
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

    if(!mLibrary) {
        std::stringstream error;
        error << "Error Creating MTLLibrary: " << compileError;
        mLogger->LogError(error.str());
        glfwTerminate();
        return -1;
    }

    mVS = [mLibrary newFunctionWithName:@"v_simple"];
    mFS = [mLibrary newFunctionWithName:@"f_simple"];
    mCommandQueue = [mDevice newCommandQueue];

    mRenderPipelineDescriptor = [MTLRenderPipelineDescriptor new];
    mRenderPipelineDescriptor.vertexFunction = mVS;
    mRenderPipelineDescriptor.fragmentFunction = mFS; 
    mRenderPipelineDescriptor.colorAttachments[0].pixelFormat = mLayer.pixelFormat;
    mRenderPipelineState = [mDevice newRenderPipelineStateWithDescriptor: mRenderPipelineDescriptor error:NULL];

    //glfwMakeContextCurrent(mWindow);
    return true;
}

Window::~Window() {
    if(mWasInitialized) {
        glfwTerminate();
    }
}

void Window::Draw(void) noexcept{
    if(glfwGetWindowAttrib(mWindow, GLFW_VISIBLE)) {
        int width, height;
        glfwGetFramebufferSize(mWindow, &width, &height);
        float ratio = width / (float) height;
        
        Matrix<float, 4, 4> p = ProjectionMatrix<float>(0.0, (float)width, (float)height, 0.0, 0.0, 1.0);
        
        mLayer.drawableSize = CGSizeMake(width, height);
        id<CAMetalDrawable> drawable = [mLayer nextDrawable];
        
        id<MTLCommandBuffer> cb = [mCommandQueue commandBuffer];
        
        MTLRenderPassDescriptor* rpd2 = [MTLRenderPassDescriptor new];
        MTLRenderPassColorAttachmentDescriptor* cd = rpd2.colorAttachments[0];
        cd.texture = drawable.texture;
        cd.loadAction = MTLLoadActionClear;
        cd.clearColor = MTLClearColorMake(1.0, 1.0, 1.0, 1.0);
        cd.storeAction = MTLStoreActionStore;
        
        id<MTLRenderCommandEncoder> rce = [cb renderCommandEncoderWithDescriptor:rpd2];
        
        [rce setRenderPipelineState:mRenderPipelineState];
        [rce setVertexBytes:(vector_float4[]){
            {  0, 0, 0, 1 },
            { -1, 1, 0 ,1 },
            {  1, 1, 0, 1 }
        } length:3 * sizeof(vector_float4) atIndex:0];
        
        
        
        [rce drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];
        
        [rce endEncoding];
        [cb presentDrawable:drawable];
        [cb commit];
    }
}

int main(int argc, char** argv) {
    ConsoleLogger logger;
    Window window(&logger);
    window.SetTitle("2048 From Scratch");
    if(!window.Init()) {
        logger.LogFatal("Window Initialization Failed. Aborting...");
        return -1;
    }

    while(!window.ShouldClose()) {
        window.Draw();
        glfwWaitEventsTimeout(1000.0);
    }

    return 0;
}
