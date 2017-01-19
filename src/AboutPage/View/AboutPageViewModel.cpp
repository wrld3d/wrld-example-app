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
                const std::string& aboutText)
                : m_openable(identity, reactionControllerModel)
                , m_buildVersion(buildVersion)
                , m_platformVersion(platformVersion)
                , m_platformHash(platformHash)
                , m_platformArchitecture(platformArchitecture)
                , m_aboutText(aboutText)
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

            const std::string AboutPageViewModel::GetContent() const
            {
                std::stringstream content;
                
                content << m_aboutText
                        << "\n\nApplication build version: " + m_buildVersion
                        << "\n\nPlatform version: " + m_platformVersion
                        << "\nPlatform hash: " + m_platformHash
                        << "\nPlatform runtime arch: " + m_platformArchitecture
                        << m_indoorPositioningType
                        << "\n";
                
                if(m_indoorPositioningType == "\nIndoor positioning type: Senion")
                {
                    content << "\n eeGeo Floor number: " << m_eegeoFloorNumber
                            << "\n Senion Floor number: " << m_senionFloorNumber
                            << "\n Latitude: " << std::setprecision(10) << m_senionLatitude
                            << "\n Longitude: " << m_senionLongitude
                            << "\n SenionApiKey: " << m_senionApiKey
                            << "\n SenionApiSecret: " << m_senionApiSecret
                            << "\n SenionFloorMap: " << m_senionFloorMapString.str()
                            << "\n SenionInteriorId: " << m_senionInteriorId
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
            
            void AboutPageViewModel::SetSenionDataType(const int32_t& eegeoFloorNumber, const int& senionFloorNumber, const double& latitude, const double& longitude)
            {
                m_eegeoFloorNumber = eegeoFloorNumber;
                m_senionFloorNumber = senionFloorNumber;
                m_senionLatitude = latitude;
                m_senionLongitude = longitude;
            }
            
            void AboutPageViewModel::SetSenionSettingsType(const std::string& apiKey, const std::string& apiSecret, const std::map<int, std::string>& floorMap, const std::string& interiorId)
            {
                m_senionApiKey = apiKey;
                m_senionApiSecret = apiSecret;
                m_senionFloorMap = floorMap;
                m_senionInteriorId = interiorId;
                
                std::map<int, std::string> map = floorMap;
                
                for(std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it)
                {
                    m_senionFloorMapString << it->second << "\n";
                }
            }
        }
    }
}
