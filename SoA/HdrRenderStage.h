/// 
///  HdrRenderStage.h
///  Seed of Andromeda
///
///  Created by Benjamin Arnold on 1 Nov 2014
///  Copyright 2014 Regrowth Studios
///  All Rights Reserved
///  
///  This file implements the HDR render stage, which
///  does HDR post processing.
///

#pragma once

#ifndef HdrRenderStage_h__
#define HdrRenderStage_h__

#include <Vorb/graphics/FullQuadVBO.h>
#include <Vorb/VorbPreDecl.inl>
#include <Vorb/graphics/GLProgram.h>

#include "IRenderStage.h"

class Camera;

class HdrRenderStage : public IRenderStage {
public:
    HdrRenderStage();

    /// @param quad: Quad used for rendering to screen
    /// @param camera: Camera used to render the scene
    void init(vg::FullQuadVBO* quad, const Camera* camera);

    /// Reloads the shader. By default, it simply
    /// disposes the shader and allows a lazy init at next draw
    virtual void reloadShader() override;

    /// Disposes and deletes the shader and turns off visibility
    /// If stage does lazy init, shader will reload at next draw
    virtual void dispose() override;

    /// Draws the render stage
    virtual void render() override;
private:
    vg::GLProgram m_glProgramBlur; ///< Motion blur enabled
    vg::GLProgram m_glProgramDoFBlur; ///< Motion blur and DoF enabled
    vg::FullQuadVBO* m_quad = nullptr; ///< For use in processing through data
    f32m4 m_oldVP = f32m4(1.0f); ///< ViewProjection of previous frame
};

#endif // HdrRenderStage_h__