#include "MacShaderLibrary.h"
#include "MetalKit/MetalKit.h"

gfs::Shader* MacShaderLibrary::GetShader(std::string name) {
    return GetMacShader(name);
}

MacShader* MacShaderLibrary::GetMacShader(std::string name) {
    auto shader = mShaders.find(name);
    if(shader == mShaders.end()) {
        auto nextShader = std::make_unique<MacShader>([mLibrary newFunctionWithName: [[NSString alloc] initWithUTF8String: name.c_str()]]);
        MacShader* res = nextShader.get();
        mShaders.emplace(name, std::move(nextShader));
        return res;
    }
    return shader->second.get();
}
