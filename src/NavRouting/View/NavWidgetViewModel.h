// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavWidgetViewModel.h"
#include "CallbackCollection.h"
#include "NavWidgetOpenableControl.h"
#include "Reaction.h"
#include "ReactionScreenStateProvider.h"

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

                Reaction::View::ReactionScreenStateProvider m_compassStateProvider;
                Reaction::View::ReactionScreenStateProvider m_interiorsStateProvider;

            public:
                NavWidgetViewModel(Eegeo::Helpers::TIdentity identity);

                ~NavWidgetViewModel();

                bool IsOpen() const override;

                void Open() override;

                void Close() override;

                void SetNavMode(SdkModel::NavRoutingMode mode) override;

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() override;

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) override;

                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) override;

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) override;

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) override;

                Reaction::View::IReactionScreenStateProvider& GetCompassStateProvider() override;
                Reaction::View::IReactionScreenStateProvider& GetInteriorsStateProvider() override;
            };
        }
    }
}
