#pragma once

#include "IExample.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"

#include "PinsModule.h"
#include <string>

#include <jni.h>
#include "EegeoWorld.h"
#include "AndroidNativeState.h"
#include "RenderContext.h"

namespace Examples
{
	/*!
     *  PinsWithAttachedJavaUIExample demonstrates how to place a pin in the 3D world, with some Java UI anchored to it
     *
     *  This is a combination of the PinsExample & the PositionJavaPinButtonExample
     */
    class PinsWithAttachedJavaUIExample : public IExample
    {
    private:
    	// pin stuff
        Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
        Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
        Eegeo::Pins::PinsModule* m_pPinsModule;
        std::string m_pinUserData;

        // java ui stuff
        AndroidNativeState& m_nativeState;
        Eegeo::Rendering::RenderContext& m_renderContext;
        Eegeo::EegeoWorld& m_world;

        int m_buttonID;
        jclass m_hudPinControllerClass;
        jobject m_hudPinController;
        jmethodID m_updateLocationMethodId;

    public:
        PinsWithAttachedJavaUIExample(
        			Eegeo::EegeoWorld& world,
        			AndroidNativeState& nativeState,
        			Eegeo::Rendering::RenderContext& renderContext,
                    Eegeo::Helpers::ITextureFileLoader& textureLoader,
                    Eegeo::Rendering::GlBufferPool& glBufferPool,
                    Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                    Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                    Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                    Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                    Eegeo::Rendering::RenderableFilters& renderableFilters,
                    const Eegeo::Camera::ICameraProvider& cameraProvider,
                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                    Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService
                    );
        virtual ~PinsWithAttachedJavaUIExample();
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();

        bool Event_TouchTap(const AppInterface::TapData& data);

    private:
        void CreateExamplePins();
        void CreateJavaUIButton();
    };
}
