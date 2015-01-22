// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationViewInterop : public IMyPinCreationConfirmationView
            {
            public:

                MyPinCreationConfirmationViewInterop(MyPinCreationConfirmationView* pView)
                    : m_pView(pView)
                {
                }

                void OnDismissed();
                void OnConfirmed();

                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void InsertConfirmedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveConfirmedCallback(Eegeo::Helpers::ICallback0& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetFullyOnScreen();
                void SetFullyOffScreen();

            private:

                Eegeo::Helpers::CallbackCollection0 m_confirmedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                MyPinCreationConfirmationView* m_pView;
            };
        }
    }
}
