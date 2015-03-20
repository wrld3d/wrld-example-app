// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ICallback.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class IMyPinDetailsView
            {
            public:
                virtual ~IMyPinDetailsView() { }

                virtual void OpenWithModel(const std::string& title,
                                           const std::string& description,
                                           const std::string& imagePath) = 0;
                virtual void Close() = 0;

                virtual void OnDismiss() = 0;
                virtual void OnRemove() = 0;

                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
