// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModule.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "IWatermarkDataRepository.h"
#include "WatermarkData.h"
#include "WatermarkView.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            void WatermarkViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<WatermarkView>().as<IWatermarkView>().singleInstance();
            }
        }
    }
}
