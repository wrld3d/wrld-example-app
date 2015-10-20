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

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            InteriorsEntitiesPinsModule::InteriorsEntitiesPinsModule(Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule,
                                                                     Eegeo::Modules::Core::RenderingModule& renderingModule,
                                                                     Eegeo::Modules::Map::MapModule& mapModule,
                                                                     const Eegeo::Rendering::ScreenProperties& screenProperties)
            : m_pInteriorsEntitiesPinsController(NULL)
            , m_pEntityPinsModule(NULL)
            , m_pEntityPinIconsTexturePageLayout(NULL)
            {
                const float entityPinSpriteWidth = 32;
                const float entityPinSpriteHeight = 32;
                
                Eegeo::Helpers::ITextureFileLoader& textureFileLoader = platformAbstractionModule.GetTextureFileLoader();
                textureFileLoader.LoadTexture(m_entityPinsTextureInfo, Helpers::ImageHelpers::GetImageNameForDevice("Interiors/icons_interior_entities", ".png"));
                
                const int iconsPerAxisInTpage = 4;
                m_pEntityPinIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(iconsPerAxisInTpage);

                Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule = mapModule.GetTerrainModelModule();
                
                m_pEntityPinsModule = Eegeo_NEW(Eegeo::Pins::PinsModule)(m_entityPinsTextureInfo.textureId,
                                                                         *m_pEntityPinIconsTexturePageLayout,
                                                                         renderingModule.GetGlBufferPool(),
                                                                         renderingModule.GetShaderIdGenerator(),
                                                                         renderingModule.GetMaterialIdGenerator(),
                                                                         renderingModule.GetVertexBindingPool(),
                                                                         renderingModule.GetVertexLayoutPool(),
                                                                         renderingModule.GetRenderableFilters(),
                                                                         terrainModelModule.GetTerrainHeightProvider(),
                                                                         entityPinSpriteWidth,
                                                                         entityPinSpriteHeight,
                                                                         Eegeo::Rendering::LayerIds::AfterWorld,
                                                                         mapModule.GetEnvironmentFlatteningService(),
                                                                         screenProperties,
                                                                         false
                                                                         );

                Eegeo::Modules::Map::Layers::InteriorsModelModule& interiorsModelModule = mapModule.GetInteriorsModelModule();
                Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule = mapModule.GetInteriorsPresentationModule();
                
                m_pInteriorsEntitiesPinsController = Eegeo_NEW(InteriorsEntitiesPinsController)(interiorsModelModule.GetInteriorsEntitiesRepository(),
                                                                                                m_pEntityPinsModule->GetController(),
                                                                                                m_pEntityPinsModule->GetRepository(),
                                                                                                interiorsPresentationModule.GetAppLevelController(),
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