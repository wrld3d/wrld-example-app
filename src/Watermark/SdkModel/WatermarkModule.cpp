// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkModule.h"
#include "WatermarkViewModel.h"
#include "WatermarkModel.h"
#include "WatermarkDataRepository.h"
#include "WatermarkData.h"
#include "WatermarkInteriorStateChangedObserver.h"
#include "WatermarkDataFactory.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            WatermarkModule::WatermarkModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             const std::string& appName,
                                             const std::string& googleAnalyticsReferrerToken,
                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                             Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                             InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                             ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pViewModel = Eegeo_NEW(View::WatermarkViewModel)(identityProvider.GetNextIdentity(), false);
                
                m_pWatermarkDataFactory = Eegeo_NEW(View::WatermarkDataFactory)(appName, googleAnalyticsReferrerToken);
                
                m_pWatermarkDataRepository = Eegeo_NEW(View::WatermarkDataRepository)();
                
                m_pWatermarkDataRepository->AddWatermarkData("eegeo", m_pWatermarkDataFactory->CreateDefaultEegeo());
        
                m_pWatermarkModel = Eegeo_NEW(WatermarkModel)();
                
                m_pWatermarkInteriorStateChangedObserver = Eegeo_NEW(WatermarkInteriorStateChangedObserver)(*m_pWatermarkModel,
                                                                                                            interiorSelectionModel,
                                                                                                            interiorsModelRepository,
                                                                                                            interiorsExplorerModel,
                                                                                                            messageBus);
                AddThirdPartyWatermarkData();
            }
            
            WatermarkModule::~WatermarkModule()
            {
                Eegeo_DELETE m_pWatermarkInteriorStateChangedObserver;
                Eegeo_DELETE m_pWatermarkModel;
                Eegeo_DELETE m_pWatermarkDataRepository;
                Eegeo_DELETE m_pWatermarkDataFactory;
                Eegeo_DELETE m_pViewModel;
            }
            
            View::IWatermarkViewModel& WatermarkModule::GetWatermarkViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& WatermarkModule::GetScreenControlViewModel() const
            {
                return m_pViewModel->GetScreenControlViewModel();
            }
            
            View::IWatermarkDataRepository& WatermarkModule::GetWatermarkDataRepository() const
            {
                return *m_pWatermarkDataRepository;
            }
            
            View::IWatermarkDataFactory& WatermarkModule::GetWatermarkDataFactory() const
            {
                return *m_pWatermarkDataFactory;
            }
            
            void WatermarkModule::AddThirdPartyWatermarkData()
            {
                const View::WatermarkData& micelloWatermarkData = m_pWatermarkDataFactory->Create("micello_logo",
                                                                                                  "3D Interiors",
                                                                                                  "Our 3D Interior maps are built automatically from map data provided by our partner Micello.\nThis partnership gives us access to over 25,000 maps globally",
                                                                                                  "https://www.micello.com",
                                                                                                  false);
                m_pWatermarkDataRepository->AddWatermarkData("micello", micelloWatermarkData);
            }
        }
    }
}
