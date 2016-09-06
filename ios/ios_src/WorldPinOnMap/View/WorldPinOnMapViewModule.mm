// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapViewModule.h"
#include "IWorldPinInFocusViewModel.h"
#include "WorldPinOnMapView.h"
#include "WorldPinOnMapController.h"
#include "WorldPinOnMapViewInterop.h"
#include "IModalityModel.h"
#include "TourHovercardView.h"
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            void WorldPinOnMapViewModule::Register(const TContainerBuilder &builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto store = context.resolve<ImageStoreWrapper>();
                                                     auto appConfig = context.resolve<ApplicationConfig::ApplicationConfiguration>();
                                                     auto view = [[WorldPinOnMapViewContainer alloc] initWithParams:appConfig->PinDiameter() :screenProperties->GetPixelScale() :store->Get()];
                                                     return std::make_shared<WorldPinOnMapViewContainerWrapper>(view);
                                                 }).singleInstance();
                
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<WorldPinOnMapViewContainerWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<IWorldPinOnMapView>().singleInstance();
            }
        }
    }
}
