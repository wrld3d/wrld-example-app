// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModule.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerViewFactory.h"
#include "GpsMarkerView.h"
#include "GpsMarkerController.h"
#include "ILocationService.h"
#include "TerrainHeightProvider.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "GlBufferPool.h"
#include "ITextureFileLoader.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {   
            void GpsMarkerModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<GpsMarkerModel>().singleInstance();
                builder->registerType<GpsMarkerViewFactory>().singleInstance();
                builder->registerType<GpsMarkerView>().singleInstance();
                builder->registerType<GpsMarkerController>().as<IGpsMarkerController>().singleInstance();
            }
            
            void GpsMarkerModule::RegisterRenderableFilters()
            {
                RegisterRenderableFilter<GpsMarkerView>();
            }
            
            void GpsMarkerModule::RegisterLeaves()
            {
                RegisterLeaf<GpsMarkerViewFactory>();
            }
        }
    }
}