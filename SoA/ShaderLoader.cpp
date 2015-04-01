#include "stdafx.h"
#include "ShaderLoader.h"

#include <Vorb/Events.hpp>
#include <Vorb/graphics/ShaderManager.h>

namespace {
    void printShaderError(Sender s, const nString& n) {
        puts("Shader Error: ");
        puts(n.c_str());
    }
    void printLinkError(Sender s, const nString& n) {
        puts("Link Error: ");
        puts(n.c_str());
    }
    void printFileIOError(Sender s, const nString& n) {
        puts("FIle IO Error: ");
        puts(n.c_str());
    }
}

CALLER_DELETE vg::GLProgram* ShaderLoader::createProgramFromFile(const vio::Path& vertPath, const vio::Path& fragPath,
                                                                 vio::IOManager* iom /*= nullptr*/, cString defines /*= nullptr*/) {
    vg::ShaderManager::onFileIOFailure += makeDelegate(printFileIOError);
    vg::ShaderManager::onShaderCompilationError += makeDelegate(printShaderError);
    vg::ShaderManager::onProgramLinkError += makeDelegate(printLinkError);

    vg::GLProgram* program = nullptr;
    while (true) {
        program = vg::ShaderManager::createProgramFromFile(vertPath, fragPath, iom, defines);
        if (program) break;

        printf("Enter any key to try recompiling with Vertex Shader: %s and Fragment Shader %s\nEnter Z to abort.\n", vertPath.getCString(), fragPath.getCString());
        char tmp;
        std::cin >> tmp;
        if (tmp == 'Z' || tmp == 'z') break;
    }

    vg::ShaderManager::onFileIOFailure -= makeDelegate(printFileIOError);
    vg::ShaderManager::onShaderCompilationError -= makeDelegate(printShaderError);
    vg::ShaderManager::onProgramLinkError -= makeDelegate(printLinkError);
    return program;
}
