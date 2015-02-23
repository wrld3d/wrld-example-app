// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "CallbackCollection.h"
#include "MyPinCreationDetailsOpenableControl.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            class MyPinCreationDetailsViewModel : public IMyPinCreationDetailsViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                MyPinCreationDetailsOpenableControl m_openable;

            public:
                MyPinCreationDetailsViewModel(Eegeo::Helpers::TIdentity identity, Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~MyPinCreationDetailsViewModel();

                bool TryAcquireReactorControl();

                bool IsOpen() const;

                void Open();

                void Close();

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            };
        }
    }
}
