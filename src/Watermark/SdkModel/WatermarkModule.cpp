// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkModule.h"
#include "WatermarkViewModel.h"
#include "WatermarkModel.h"
#include "WatermarkDataRepository.h"
#include "WatermarkData.h"
#include "WatermarkInteriorStateChangedObserver.h"
#include "WatermarkDataFactory.h"
#include "ApplicationConfiguration.h"
#include "InteriorSelectionModel.h"
#include "InteriorsModelRepository.h"
#include "InteriorsExplorerModel.h"
#include "InteriorInteractionModel.h"
#include "IVisualMapService.h"
#include "IMetricsService.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            void WatermarkModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::WatermarkViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), true);
                                                   }).as<View::IWatermarkViewModel>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       auto appConfig = context.resolve<ApplicationConfig::ApplicationConfiguration>();
                                                       return std::make_shared<View::WatermarkDataFactory>(appConfig->Name(), appConfig->GoogleAnalyticsReferrerToken());
                                                   }).as<View::IWatermarkDataFactory>().singleInstance();
                builder->registerType<View::WatermarkDataRepository>().as<View::IWatermarkDataRepository>().singleInstance();
                builder->registerType<WatermarkModel>().singleInstance();
                builder->registerType<WatermarkInteriorStateChangedObserver>().singleInstance();
            }
            
            void WatermarkModule::RegisterLeaves()
            {
                RegisterLeaf<WatermarkInteriorStateChangedObserver>();
                
                auto repo = Resolve<View::IWatermarkDataRepository>();
                auto factory = Resolve<View::IWatermarkDataFactory>();
                repo->AddWatermarkData("eegeo", factory->CreateDefaultEegeo());
                
                const View::WatermarkData& micelloWatermarkData = factory->Create("micello_logo",
                                                                                                  "3D Interiors",
                                                                                                  "Our 3D Interior maps are built automatically from map data provided by our partner Micello.\nThis partnership gives us access to over 25,000 maps globally",
                                                                                                  "https://www.micello.com",
                                                                                                  false);

                repo->AddWatermarkData("micello", micelloWatermarkData);
            }
        }
    }
}
