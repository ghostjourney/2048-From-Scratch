#include "MacShaderLibraryBuilder.h"
#include "MacShaderLibrary.h"

void MacShaderLibraryBuilder::SetMTLDevice(id<MTLDevice> device) {
    mDevice = device;
}

void MacShaderLibraryBuilder::AddShader(std::string& name, std::string& shader_src) {
    mShadersSrcs.emplace_back(std::pair(name, shader_src));
}

std::unique_ptr<gfs::ShaderLibrary> MacShaderLibraryBuilder::BuildLibrary(void) {
    return BuildMacShaderLibrary();
}

std::unique_ptr<MacShaderLibrary> MacShaderLibraryBuilder::BuildMacShaderLibrary(void) {
    auto library = std::make_unique<MacShaderLibrary>();
    NSMutableString* librarySrc = [[NSMutableString alloc] init];

    MTLCompileOptions* compileOptions = [MTLCompileOptions new];
    compileOptions.languageVersion = MTLLanguageVersion2_4;

    NSError* compileError;

    for(const auto& i: mShadersSrcs) {
        [librarySrc appendString: [[NSString alloc] initWithUTF8String: i.second.c_str()]];
        [librarySrc appendString: @"\n"];
    }

    library->mLibrary = [mDevice newLibraryWithSource: librarySrc options: compileOptions error: &compileError];

    if(!library->mLibrary) {
        NSLog(@"Error Creating MTLLibrary");
        return nullptr;
    }
    return library;
}

void MacShaderLibraryBuilder::AddShaderBlock(std::string& shader_src) {
    mShadersSrcs.emplace_back(std::pair("", shader_src));
}
