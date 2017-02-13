// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include <map>
#include <sstream>

#include "InteriorsLocationServiceProvider.h"
#include "InteriorSelectionModel.h"
#include "IPSConfigurationParser.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            const std::string IndoorPositionTypeMessageHeader = "\nIndoor positioning type: ";
            const std::string DefaultIndoorPositioning = "GPS";
            const std::string NoIndoorPositioning = "";

            InteriorsLocationServiceProvider::InteriorsLocationServiceProvider(InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                               Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                               Eegeo::Helpers::CurrentLocationService::CurrentLocationService& currentLocationService,
                                                                               Eegeo::Location::ILocationService& defaultLocationService,
                                                                               std::map<std::string, Eegeo::Location::ILocationService&> interiorLocationServices,
                                                                               Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository,
                                                                               ExampleAppMessaging::TMessageBus& messageBus)
            : m_currentLocationService(currentLocationService)
            , m_defaultLocationService(defaultLocationService)
            , m_interiorLocationServices(interiorLocationServices)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_messageBus(messageBus)
            , m_interiorExplorerEnteredCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &InteriorsLocationServiceProvider::OnInteriorExplorerExit)
            , m_interiorMetaDataRepository(interiorMetaDataRepository)
            {
                m_interiorsExplorerModel.InsertInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.InsertInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            InteriorsLocationServiceProvider::~InteriorsLocationServiceProvider()
            {
                m_interiorsExplorerModel.RemoveInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.RemoveInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerEntered()
            {
                Eegeo::Resources::Interiors::InteriorId interiorId = m_interiorSelectionModel.GetSelectedInteriorId();
                std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> interiorTrackingInfoList;
                
                if(interiorId.IsValid())
                {
                    InteriorsPosition::TryAndGetInteriorTrackingInfo(interiorTrackingInfoList, interiorId, m_interiorMetaDataRepository);
                }
                else
                {
                    return;
                }

                std::stringstream indoorPositionTypeMessage;
                indoorPositionTypeMessage << IndoorPositionTypeMessageHeader;

                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>& trackingInfoMap = interiorTrackingInfoList;
                const std::map<std::string, ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo>::const_iterator it = trackingInfoMap.find(interiorId.Value());

                if (it != trackingInfoMap.end())
                {
                    const ExampleApp::ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo &trackingInfo = it->second;
                    std::map<std::string, Eegeo::Location::ILocationService&>::const_iterator interiorLocationService = m_interiorLocationServices.find(trackingInfo.GetType());
                    if (interiorLocationService != m_interiorLocationServices.end())
                    {
                        std::stringstream interiorLocationServiceUseMessage;
                        interiorLocationServiceUseMessage << "using " << trackingInfo.GetType() << "location service";
                        Eegeo_TTY(interiorLocationServiceUseMessage.str().c_str());

                        indoorPositionTypeMessage << trackingInfo.GetType();
                        m_currentLocationService.SetLocationService(interiorLocationService->second);
                        m_messageBus.Publish(AboutPage::AboutPageIndoorPositionTypeMessage(indoorPositionTypeMessage.str()));
                    }
                }
                else
                {
                    indoorPositionTypeMessage << DefaultIndoorPositioning;
                    m_messageBus.Publish(AboutPage::AboutPageIndoorPositionTypeMessage(indoorPositionTypeMessage.str()));
                }
            }
            
            void InteriorsLocationServiceProvider::OnInteriorExplorerExit()
            {
                Eegeo_TTY("using default location service");
                m_currentLocationService.SetLocationService(m_defaultLocationService);
                m_messageBus.Publish(AboutPage::AboutPageIndoorPositionTypeMessage(NoIndoorPositioning));
            }
        }
    }
}
