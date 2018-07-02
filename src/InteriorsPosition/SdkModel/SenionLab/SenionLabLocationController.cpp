// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "SenionLabLocationController.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "IPSConfigurationParser.h"
#include "AboutPageIndoorPositionSettingsMessage.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            namespace SenionLab
            {
                SenionLabLocationController::SenionLabLocationController(SenionLabLocationService& locationService,
                                                                         ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                         const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                         const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                : m_locationService(locationService)
                , m_appModeModel(appModeModel)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeChangedCallback(this, &SenionLabLocationController::OnAppModeChanged)
                , m_interiorMetaDataRepository(interiorMetaDataRepository)
                {
                    m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                SenionLabLocationController::~SenionLabLocationController()
                {
                    m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
                }
                
                namespace
                {
                    bool IsInSenionIndoorMap(const AppModes::SdkModel::AppMode& appMode,
                                             const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                             const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
                    {
                        if(appMode != AppModes::SdkModel::InteriorMode)
                        {
                            return false;
                        }
                        
                        if(!interiorId.IsValid())
                        {
                            return false;
                        }
                        
                        typedef std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;
                        TrackingInfoMap trackingInfoMap;
                        InteriorsPosition::TryAndGetInteriorTrackingInfo(trackingInfoMap, interiorId, interiorMetaDataRepository);
                        
                        const TrackingInfoMap::const_iterator trackingInfoEntry = trackingInfoMap.find(interiorId.Value());
                        
                        if (trackingInfoEntry == trackingInfoMap.end())
                        {
                            return false;
                        }
                        
                        const auto& trackingInfo = trackingInfoEntry->second;
                        
                        return trackingInfo.GetType() == "Senion";
                    }
                }
                
                void SenionLabLocationController::OnAppModeChanged()
                {
                    m_locationService.StopUpdating();
                    
                    const auto appMode = m_appModeModel.GetAppMode();
                    const auto selectedInteriorId = m_interiorSelectionModel.GetSelectedInteriorId();
                    
                    if(IsInSenionIndoorMap(appMode, selectedInteriorId, m_interiorMetaDataRepository))
                    {
                        m_locationService.StartUpdating();
                    }
                    else
                    {
                        m_locationService.StopUpdating();
                        m_locationService.RestoreDefaultState();
                    }
                }
            }
        }
    }
}
