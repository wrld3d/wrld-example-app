// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkViewModule.h"
#include "WatermarkView.h"
#include "ScreenProperties.h"
#include "WatermarkController.h"
#include "WatermarkViewInterop.h"
#include "IWatermarkDataRepository.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            void WatermarkViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto view = [[WatermarkView alloc] initWithDimensions
                                                                :screenProperties->GetScreenWidth()
                                                                :screenProperties->GetScreenHeight()
                                                                :screenProperties->GetPixelScale()];
                                                     return std::make_shared<WatermarkViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<WatermarkViewWrapper>();
                                                     auto interop = [view->Get() getInterop];
                                                     return Hypodermic::makeExternallyOwned(*interop);
                                                 }).as<IWatermarkView>().singleInstance();
            }
        }
    }
}
