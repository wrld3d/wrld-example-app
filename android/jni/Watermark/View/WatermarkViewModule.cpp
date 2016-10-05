// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModule.h"
#include "AndroidAppThreadAssertionMacros.h"
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
				ASSERT_UI_THREAD
				builder->registerType<WatermarkView>().as<IWatermarkView>().singleInstance();
			}

			void WatermarkViewModule::RegisterLeaves()
			{
				ASSERT_UI_THREAD
				RegisterLeaf<IWatermarkView>();
			}
        }
    }
}
