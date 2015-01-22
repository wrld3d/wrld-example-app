// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class IMyPinCreationConfirmationView : public ScreenControl::View::IScreenControlView
            {
            public:

                virtual ~IMyPinCreationConfirmationView() { }

                virtual void OnDismissed() = 0;
                virtual void OnConfirmed() = 0;

                virtual void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
