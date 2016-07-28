// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntitiesPinsModule.h"
#include "InteriorsEntitiesPinsController.h"

#include "IPlatformAbstractionModule.h"
#include "RenderingModule.h"
#include "MapModule.h"
#include "TerrainModelModule.h"
#include "InteriorsModelModule.h"
#include "InteriorsPresentationModule.h"

#include "RegularTexturePageLayout.h"

#include "PinsModule.h"
#include "ITextureFileLoader.h"
#include "InteriorsLabelController.h"
#include "ImagePathHelpers.h"
#include "IWorldPinIconMapping.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            InteriorsEntitiesPinsModule::InteriorsEntitiesPinsModule(Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule,
                                                                     Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                                     Eegeo::Modules::Map::MapModule& mapModule,
                                                                     const WorldPins::SdkModel::IWorldPinIconMapping& worldPinIconMapping,
                                                                     const Eegeo::Rendering::ScreenProperties& screenProperties)
            : m_pInteriorsEntitiesPinsController(NULL)
            , m_pEntityPinsModule(NULL)
            , m_pEntityPinIconsTexturePageLayout(NULL)
            {
                
                Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = mapModule.GetTerrainModelModule();

                m_pEntityPinsModule = Eegeo::Pins::PinsModule::CreateWithAtlas(renderingModule,
                                                                      platformAbstractionModule,
                                                                      mapModule,
                                                                      worldPinIconMapping.GetTextureInfo().textureId,
                                                                      worldPinIconMapping.GetTexturePageLayout(),
                                                                      Eegeo::Rendering::LayerIds::AfterWorld,
                                                                      screenProperties);

                Eegeo::Modules::Map::Layers::InteriorsModelModule& interiorsModelModule = mapModule.GetInteriorsModelModule();
                Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
                
                m_pInteriorsEntitiesPinsController = Eegeo_NEW(InteriorsEntitiesPinsController)(interiorsModelModule.GetInteriorsEntitiesRepository(),
                                                                                                m_pEntityPinsModule->GetController(),
                                                                                                m_pEntityPinsModule->GetRepository(),
                                                                                                worldPinIconMapping,
                                                                                                interiorsPresentationModule.GetInteriorInteractionModel(),
                                                                                                interiorsPresentationModule.GetInteriorTransitionModel(),
                                                                                                interiorsPresentationModule.GetInteriorsLabelsController(),
                                                                                                terrainModelModule.GetTerrainHeightProvider());
                
                
            }
            
            InteriorsEntitiesPinsModule::~InteriorsEntitiesPinsModule()
            {
                Eegeo_DELETE m_pInteriorsEntitiesPinsController;
                Eegeo_DELETE m_pEntityPinsModule;
                Eegeo_DELETE m_pEntityPinIconsTexturePageLayout;
                Eegeo_GL(glDeleteTextures(1, &m_entityPinsTextureInfo.textureId));
            }
            
            IInteriorsEntitiesPinsController& InteriorsEntitiesPinsModule::GetInteriorsEntitiesPinsController()
            {
                return *m_pInteriorsEntitiesPinsController;
            }
            
            Eegeo::Pins::PinsModule& InteriorsEntitiesPinsModule::GetPinsModule()
            {
                return *m_pEntityPinsModule;
            }
        }
    }
}