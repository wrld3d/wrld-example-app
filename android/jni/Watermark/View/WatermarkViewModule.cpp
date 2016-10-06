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
				builder->registerType<WatermarkView>().as<IWatermarkView>().singleInstance();
			}

			void WatermarkViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("WatermarkViewModule::RegisterUiLeaves begin");
				ASSERT_UI_THREAD
				RegisterLeaf<IWatermarkView>();
				Eegeo_TTY("WatermarkViewModule::RegisterUiLeaves end");
			}
        }
    }
}
