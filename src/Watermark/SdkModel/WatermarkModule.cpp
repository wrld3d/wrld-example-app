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

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            void WatermarkModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<View::WatermarkViewModel>(context.resolve<Eegeo::Helpers::IIdentityProvider>(), false);
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
            
            /*            
            void WatermarkModule::AddThirdPartyWatermarkData()
            {
                //m_pWatermarkDataRepository->AddWatermarkData("eegeo", m_pWatermarkDataFactory->CreateDefaultEegeo());

                const View::WatermarkData& micelloWatermarkData = m_pWatermarkDataFactory->Create("micello_logo",
                                                                                                  "3D Interiors",
                                                                                                  "Our 3D Interior maps are built automatically from map data provided by our partner Micello.\nThis partnership gives us access to over 25,000 maps globally",
                                                                                                  "https://www.micello.com",
                                                                                                  false);
                m_pWatermarkDataRepository->AddWatermarkData("micello", micelloWatermarkData);
            } */
        }
    }
}
