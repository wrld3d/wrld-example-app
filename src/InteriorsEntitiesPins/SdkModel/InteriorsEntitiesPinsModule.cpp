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
#include "EegeoWorld.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"
#include "WorldPinsPlatformServices.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            void InteriorsEntitiesPinsModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<WorldPins::SdkModel::InteriorPinsPlatformServices>().singleInstance();
                builder->registerType<InteriorsEntitiesPinsController>().as<IInteriorsEntitiesPinsController>().singleInstance();
            }
        }
    }
}