#include "MacShader.h"
#include "MetalKit/MetalKit.h"

MacShader::MacShader(id<MTLFunction> shader) {
    mShader = shader;
}

id<MTLFunction> MacShader::GetShader() {
    return mShader;
}
