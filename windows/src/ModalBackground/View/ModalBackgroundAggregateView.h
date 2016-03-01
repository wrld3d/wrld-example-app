// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundView.h"
#include "WindowsNativeState.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundAggregateView: public Modality::View::IModalBackgroundView
            {
            public:
                ModalBackgroundAggregateView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);
                ~ModalBackgroundAggregateView();

                void SetFullyActive();
                void SetFullyInactive();
                void SetActiveStateToIntermediateValue(float modality);

                void InsertTappedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleViewTapped();

            private:

                WindowsNativeState& m_nativeState;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::CallbackCollection0 m_tappedCallbacks;
            };
        }
    }
}
