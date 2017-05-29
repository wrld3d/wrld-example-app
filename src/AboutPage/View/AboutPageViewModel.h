// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAboutPageViewModel.h"
#include "CallbackCollection.h"
#include "AboutPageOpenableControl.h"
#include "Reaction.h"
#include "AboutPage.h"
#include <sstream>

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageViewModel : public IAboutPageViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                AboutPageOpenableControl m_openable;

                const std::string m_buildVersion;
                const std::string m_platformVersion;
                const std::string m_platformHash;
                const std::string m_platformArchitecture;
                const std::string m_aboutText;
                std::string m_appName;
                std::string m_indoorPositioningType;
                int32_t m_eegeoFloorIndex;
                int m_senionFloorNumber;
                std::string m_indoorAtlasFloorId;
                double m_latitude;
                double m_longitude;
                std::string m_apiKey;
                std::string m_apiSecret;
                std::map<int, std::string> m_floorMap;
                std::stringstream m_floorMapString;
                std::string m_interiorId;

            public:
                AboutPageViewModel(
                    Eegeo::Helpers::TIdentity identity,
                    Reaction::View::IReactionControllerModel& reactionControllerModel,
                    const std::string& buildVersion,
                    const std::string& platformVersion,
                    const std::string& platformHash,
                    const std::string& platformArchitecture,
                    const std::string& aboutText,
                    const std::string& appName);

                ~AboutPageViewModel();

                bool TryAcquireReactorControl();
                bool IsOpen() const;
                void Open();
                void Close();
                
                void UpdateApplicationName(const std::string& appName);

                const std::string GetContent(bool showHiddenContent) const;
                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                
                void SetIndoorPositioningType(const std::string& indoorPositioningType);
                void SetIndoorPositionSettings(const std::string& apiKey, const std::string& apiSecret, const std::map<int, std::string>& floorMap, const std::string& interiorId);
                void SetSenionData(const int32_t& eegeoFloorNumber, const int& senionFloorNumber, const double& latitude, const double& longitude);
                void SetIndoorAtlasData(const int32_t& eegeoFloorNumber, const std::string& indoorAtlasFloorId, const double& latitude, const double& longitude);
            };
        }
    }
}
