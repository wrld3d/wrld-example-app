// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavWidgetViewModel.h"
#include "CallbackCollection.h"
#include "NavWidgetOpenableControl.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetViewModel : public INavWidgetViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                NavWidgetOpenableControl m_openable;

            public:
                NavWidgetViewModel(Eegeo::Helpers::TIdentity identity,
                                   Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~NavWidgetViewModel();

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
