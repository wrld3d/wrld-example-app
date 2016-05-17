// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModalBackgroundView.h"

#include "AndroidNativeState.h"
#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            class ModalBackgroundAggregateView: public Modality::View::IModalBackgroundView
            {
            public:
                ModalBackgroundAggregateView(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);
                ~ModalBackgroundAggregateView();

                void SetFullyActive();
                void SetFullyInactive();
                void SetActiveStateToIntermediateValue(float modality);

                void InsertTappedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleViewTapped();

            private:

                AndroidNativeState& m_nativeState;

                jclass m_uiViewClass;
                jobject m_uiView;

                Eegeo::Helpers::CallbackCollection0 m_tappedCallbacks;
                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
