// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGpsMarkerModule.h"
#include "GpsMarker.h"
#include "Rendering.h"
#include "GlHelpers.h"
#include "Modules.h"
#include "Location.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModule : public IGpsMarkerModule
            {
            public:
                
                GpsMarkerModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                Eegeo::Location::ILocationService& locationService,
                                Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                ExampleAppMessaging::TMessageBus& messageBus);
                ~GpsMarkerModule();
                
                IGpsMarkerController& GetGpsMarkerController();
                
            private:
                
                GpsMarkerModel* m_pModel;
                GpsMarkerView* m_pView;
                IGpsMarkerController* m_pController;
                
                Eegeo::Rendering::Shaders::BatchedSpriteShader* m_pSpriteShader;
                Eegeo::Rendering::Materials::BatchedSpriteMaterial* m_pGpsIconMaterial;
                Eegeo::Rendering::Renderables::BatchedSpriteRenderable* m_pGpsIconRenderable;
                
                Eegeo::Helpers::GLHelpers::TextureInfo m_gpsIconTexture;
                
                Eegeo::Rendering::RenderableFilters& m_renderableFilters;
            };
        }
    }
}