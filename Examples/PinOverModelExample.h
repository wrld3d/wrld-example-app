//
//  PinOverModelExample.h
//  ExampleApp
//
//  Created by Scott on 06/03/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__PinOverModelExample__
#define __ExampleApp__PinOverModelExample__

#include "IExample.h"

#include "Rendering.h"
#include "Camera.h"
#include "ITextureFileLoader.h"
#include "IFileIO.h"
#include "PinsModule.h"
#include <string>
#include "IAsyncTextureRequestor.h"
#include "GlobalFogging.h"
#include "Model.h"

namespace Examples
{
    /*!
     *  PinsExample demonstrates the display of Pins within the 3D world.
     *  Pins are placed relative to the underlying terrain and displayed as Sprites which always face the camera.
     *  This example also demonstrates how Pins can be selected by testing against their screen bounds.
     *  Pin add / remove functionality is demonstrated by adding / removing pin 0 every 3 seconds.
     */
    class PinOverModelExample : public IExample
    {
    private:
        Eegeo::Rendering::ITexturePageLayout* m_pPinIconsTexturePageLayout;
        Eegeo::Helpers::GLHelpers::TextureInfo m_pinIconsTexture;
        Eegeo::Pins::PinsModule* m_pPinsModule;
        std::string m_pin0UserData;
        
        Eegeo::Pins::Pin* m_pPin0;
        
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Helpers::IFileIO& fileIO;
        Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor;
        Eegeo::Lighting::GlobalFogging& globalFogging;
        
        Eegeo::Model* pModel;
        
    public:
        PinOverModelExample(
                            Eegeo::Helpers::ITextureFileLoader& textureLoader,
                            Eegeo::Rendering::GlBufferPool& glBufferPool,
                            Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                            Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                            Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                            Eegeo::Rendering::RenderableFilters& renderableFilters,
                            const Eegeo::Camera::ICameraProvider& cameraProvider,
                            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                            Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                            Eegeo::Rendering::RenderContext& renderContext,
                            Eegeo::Helpers::IFileIO& fileIO,
                            Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                            Eegeo::Lighting::GlobalFogging& fogging
                            );
        virtual ~PinOverModelExample();
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
        
    private:
        void CreateExamplePins();
    };
}

#endif /* defined(__ExampleApp__PinOverModelExample__) */
