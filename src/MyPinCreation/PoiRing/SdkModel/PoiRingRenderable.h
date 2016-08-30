// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RenderableBase.h"
#include "IFileIO.h"
#include "AsyncTexturing.h"
#include "Lighting.h"
#include "Model.h"
#include "Camera.h"
#include "Modules.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class PoiRingRenderable : public Eegeo::Rendering::RenderableBase
                {
                public:
                    PoiRingRenderable(const std::shared_ptr<Eegeo::Modules::Core::RenderingModule>& renderingModule,
                                      const std::shared_ptr<Eegeo::Helpers::IFileIO>& fileIO,
                                      const std::shared_ptr<Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor>& textureRequestor,
                                      const std::shared_ptr<Eegeo::Lighting::GlobalFogging>& globalFogging);

                    ~PoiRingRenderable();

                    void Render(Eegeo::Rendering::GLState& glState) const;

                    void SetSphereMvp(const Eegeo::m44& mvp) const;

                    void SetInnerSphereScale(const float scale);
                private:
                    Eegeo::Model* m_pSphere;
                    const std::shared_ptr<Eegeo::Lighting::GlobalFogging> m_fogging;

                    Eegeo::Rendering::Shaders::ColorShader* m_pColorShader;
                    Eegeo::Rendering::Materials::ColorMaterial* m_pColorMaterial;
                    Eegeo::Rendering::Renderables::WorldMeshRenderable* m_pQuadRenderable;

                    float m_innerSphereScale;

                    void RenderClearStencil(Eegeo::Rendering::GLState& glState) const;
                    void RenderSpheres(Eegeo::Rendering::GLState& glState) const;
                    void RenderRingEffects(Eegeo::Rendering::GLState& glState) const;
                };
            }
        }
    }
}
