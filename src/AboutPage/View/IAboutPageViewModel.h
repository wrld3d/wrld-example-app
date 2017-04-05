// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class IAboutPageViewModel
            {
            public:
                virtual ~IAboutPageViewModel() { }

                virtual bool TryAcquireReactorControl() = 0;

                virtual bool IsOpen() const = 0;

                virtual void Open() = 0;

                virtual void Close() = 0;
                
                virtual void UpdateApplicationName(const std::string&) = 0;

                virtual const std::string GetContent(bool showHiddenContent) const = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                
                virtual void SetIndoorPositioningType(const std::string& indoorPositioningType) = 0;
                
                virtual void SetSenionDataType(const int& eegeoFloorNumber ,const int32_t& senionFloorNumber, const double& latitude, const double& longitude) = 0;
                
                virtual void SetSenionSettingsType(const std::string& floorNumber, const std::string& latitude, const std::map<int, std::string>& longitude, const std::string& interiorId) = 0;
            };
        }
    }
}
