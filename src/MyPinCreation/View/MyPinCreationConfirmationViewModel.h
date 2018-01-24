// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "MyPinCreationScreenControl.h"
#include "IIdentity.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "MyPinCreation.h"
#include "CallbackCollection.h"
#include "MyPinCreationConfirmationOpenableControl.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationConfirmationViewModel : public IMyPinCreationConfirmationViewModel, private Eegeo::NonCopyable
            {
            public:

                MyPinCreationConfirmationViewModel(Eegeo::Helpers::TIdentity identity,
                                                   bool isInitiallyOnScreen);


                Eegeo::Helpers::TIdentity GetIdentity() const;

                void AddToScreen();

                void RemoveFromScreen();

                void InsertOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback);

                void RemoveOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback);

                bool IsOffScreen() const;

                bool IsOnScreen() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel();

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControlViewModel();

                bool TryOpen();

                void Close();

                void Open();

                void InsertOpenCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveOpenCallback(Eegeo::Helpers::ICallback0& callback);

            private:
                MyPinCreationScreenControl m_screenControl;
                MyPinCreationConfirmationOpenableControl m_openable;
                Eegeo::Helpers::CallbackCollection0 m_openCallbacks;
            };
        }
    }
}
