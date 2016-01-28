// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundAggregateView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "Types.h"
#include "UpdateNativeModalBackgroundMessage.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            ModalBackgroundAggregateView::ModalBackgroundAggregateView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus)
                : m_nativeState(nativeState)
                , m_messageBus(messageBus)
            {

            }

            ModalBackgroundAggregateView::~ModalBackgroundAggregateView()
            {

            }

            void ModalBackgroundAggregateView::SetFullyActive()
            {
                SetActiveStateToIntermediateValue(1.0f);
            }

            void ModalBackgroundAggregateView::SetFullyInactive()
            {
                SetActiveStateToIntermediateValue(0.0f);
            }

            void ModalBackgroundAggregateView::SetActiveStateToIntermediateValue(float modality)
            {
                m_messageBus.Publish(Modality::UpdateNativeModalBackgroundMessage(modality, false));
            }

            void ModalBackgroundAggregateView::InsertTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_tappedCallbacks.AddCallback(callback);
            }

            void ModalBackgroundAggregateView::RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_tappedCallbacks.RemoveCallback(callback);
            }

            void ModalBackgroundAggregateView::HandleViewTapped()
            {
                m_tappedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
