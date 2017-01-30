// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPinCreation.h"
#include "IPoiRingModule.h"
#include "Modules.h"
#include "Rendering.h"
#include "IdTypes.h"
#include "Terrain.h"
#include "GLHelpers.h"
#include "AppModes.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                class PoiRingModule : public IPoiRingModule
                {
                public:
                    PoiRingModule(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                  Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                  Eegeo::Modules::Core::RenderingModule& renderingModule,
                                  Eegeo::Modules::Core::AsyncLoadersModule& asyncLoadersModule,
                                  Eegeo::Modules::Core::LightingModule& lightingModule,
                                  Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                  Eegeo::Modules::Map::MapModule& mapModule,
                                  ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                  Eegeo::Rendering::ScreenProperties& screenProperties,
                                  const bool interiorsAffectedByFlattening,
                                  const bool isInKioskMode);

                    ~PoiRingModule();

                    IPoiRingController& GetPoiRingController() const;
                    IPoiRingTouchController& GetPoiRingTouchController() const;


                private:
                    PoiRingView* m_pPoiRingView;
                    PoiRingRenderable* m_pPoiRingRenderable;
                    Eegeo::Rendering::Shaders::BatchedSpriteShader* m_pSpriteShader;
                    Eegeo::Rendering::Materials::BatchedSpriteMaterial* m_pPoiRingIconMaterial;
                    Eegeo::Rendering::Renderables::BatchedSpriteRenderable* m_pPoiRingIconRenderable;

                    Eegeo::Helpers::GLHelpers::TextureInfo m_poiRingIconTexture;

                    Eegeo::Resources::Terrain::Collision::TerrainRayPicker* m_pTerrainRayPicker;
                    Eegeo::Rendering::RenderableFilters& m_renderableFilters;

                    IPoiRingController* m_pPoiRingController;
                    IPoiRingTouchController* m_pPoiRingTouchController;
                };
            }
        }
    }
}
