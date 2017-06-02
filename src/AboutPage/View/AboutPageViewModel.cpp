// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewModel.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageViewModel::AboutPageViewModel(
                Eegeo::Helpers::TIdentity identity,
                Reaction::View::IReactionControllerModel& reactionControllerModel,
                const std::string& buildVersion,
                const std::string& platformVersion,
                const std::string& platformHash,
                const std::string& platformArchitecture,
                const std::string& aboutText,
                const std::string& appName)
                : m_openable(identity, reactionControllerModel)
                , m_buildVersion(buildVersion)
                , m_platformVersion(platformVersion)
                , m_platformHash(platformHash)
                , m_platformArchitecture(platformArchitecture)
                , m_aboutText(aboutText)
                , m_appName(appName)
                , m_indoorPositioningType("")
            {
                
            }

            AboutPageViewModel::~AboutPageViewModel()
            {
                
            }

            bool AboutPageViewModel::TryAcquireReactorControl()
            {
                return m_openable.TryAcquireReactorControl();
            }

            bool AboutPageViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }

            const std::string AboutPageViewModel::GetContent(bool showHiddenContent) const
            {
                std::stringstream content;
                
                content << m_aboutText
                        << "\n\nApplication build version: " + m_buildVersion
                        << "\n\nPlatform version: " + m_platformVersion
                        << "\nPlatform hash:\n" + m_platformHash
                        << "\nPlatform runtime arch: " + m_platformArchitecture
                        << "\nApplication Name: " + m_appName
                        << m_indoorPositioningType
                        << "\n";
                
                if(m_indoorPositioningType == "\nIndoor positioning type: Senion" && showHiddenContent)
                {
                    content << "\n eeGeo Floor number: " << m_eegeoFloorIndex
                            << "\n Senion Floor number: " << m_senionFloorNumber
                            << "\n Latitude: " << std::setprecision(10) << m_latitude
                            << "\n Longitude: " << m_longitude
                            << "\n ApiKey: " << m_apiKey
                            << "\n ApiSecret: " << m_apiSecret
                            << "\n FloorMap: " << m_floorMapString.str()
                            << "\n InteriorId: " << m_interiorId
                            << "\n";
                }
                else if(m_indoorPositioningType == "\nIndoor positioning type: IndoorAtlas" && showHiddenContent)
                {
                    content << "\n eeGeo Floor number: " << m_eegeoFloorIndex
                            << "\n IndoorAtlas Floor id: " << m_indoorAtlasFloorId
                            << "\n Latitude: " << std::setprecision(10) << m_latitude
                            << "\n Longitude: " << m_longitude
                            << "\n ApiKey: " << m_apiKey
                            << "\n ApiSecret: " << m_apiSecret
                            << "\n FloorMap: " << m_floorMapString.str()
                            << "\n InteriorId: " << m_interiorId
                            << "\n";
                }
                
                return content.str();
            }

            void AboutPageViewModel::Open()
            {
                if(!IsOpen())
                {
                    if(m_openable.Open())
                    {
                        m_openedCallbacks.ExecuteCallbacks();
                    }
                }
            }

            void AboutPageViewModel::Close()
            {
                if(IsOpen())
                {
                    {
                        const bool closed = m_openable.Close();
                        Eegeo_ASSERT(closed, "Failed to close");
                    }

                    m_closedCallbacks.ExecuteCallbacks();
                }
            }
            
            void AboutPageViewModel::UpdateApplicationName(const std::string& appName)
            {
                m_appName = appName;
            }
            
            OpenableControl::View::IOpenableControlViewModel& AboutPageViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void AboutPageViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void AboutPageViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void AboutPageViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void AboutPageViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
            
            void AboutPageViewModel::SetIndoorPositioningType(const std::string& indoorPositioningType)
            {
                m_indoorPositioningType = indoorPositioningType;
            }
            
            void AboutPageViewModel::SetSenionData(const int32_t& eegeoFloorNumber,
                                                   const int& senionFloorNumber,
                                                   const double& latitude,
                                                   const double& longitude)
            {
                m_eegeoFloorIndex = eegeoFloorNumber;
                m_senionFloorNumber = senionFloorNumber;
                m_latitude = latitude;
                m_longitude = longitude;
            }

            void AboutPageViewModel::SetIndoorAtlasData(const int &eegeoFloorindex,
                                                        const std::string &indoorAtlasFloorId,
                                                        const double &latitude,
                                                        const double &longitude)
            {
                m_eegeoFloorIndex = eegeoFloorindex;
                m_indoorAtlasFloorId = indoorAtlasFloorId;
                m_latitude = latitude;
                m_longitude = longitude;
            }

            void AboutPageViewModel::SetIndoorPositionSettings(const std::string& apiKey,
                                                               const std::string& apiSecret,
                                                               const std::map<int, std::string>& floorMap,
                                                               const std::string& interiorId)
            {
                m_apiKey = apiKey;
                m_apiSecret = apiSecret;
                m_floorMap = floorMap;
                m_interiorId = interiorId;
                
                std::map<int, std::string> map = floorMap;

                m_floorMapString.str(std::string());
                for(std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
                {
                    m_floorMapString << it->second << "\n";
                }
            }
        }
    }
}
