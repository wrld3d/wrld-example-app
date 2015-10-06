// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include <string>

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class IMyPinCreationDetailsView
            {
            public:
                virtual ~IMyPinCreationDetailsView() { }

                virtual void Open() = 0;
                virtual void Close() = 0;

                virtual void OnDismissed() = 0;
                virtual void OnConfirmed() = 0;

                virtual void ConnectivityChanged(const bool hasConnectivity, const bool shouldVerifyShareSettings) = 0;

                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual std::string GetTitle() const = 0;
                virtual std::string GetDescription() const = 0;
                virtual bool ShareSelected() const = 0;
                virtual Byte* GetImageBuffer() const = 0;
                virtual size_t GetImageSize() const = 0;
            };
        }
    }
}
