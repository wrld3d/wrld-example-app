// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingModule.h"

#include "PoiRingRenderable.h"
#include "PoiRingView.h"
#include "PoiRingController.h"
#include "PoiRingTouchCOntroller.h"
#include "GlobalFogging.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "VertexLayoutPool.h"
#include "GlBufferPool.h"
#include "IMyPinCreationModel.h"
#include "TerrainHeightProvider.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"
#include "ScreenProperties.h"
#include "IAppModeModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                void PoiRingModule::Register(const TContainerBuilder& builder)
                {
                    builder->registerType<PoiRingRenderable>().singleInstance();
                    builder->registerType<PoiRing::SdkModel::PoiRingView>().singleInstance();
                    builder->registerType<PoiRingController>().as<IPoiRingController>().singleInstance();
                    builder->registerType<PoiRingTouchController>().as<IPoiRingTouchController>().singleInstance();
                }
            }
        }
    }
}
