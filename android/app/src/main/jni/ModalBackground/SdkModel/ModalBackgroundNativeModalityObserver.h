// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ModalBackgroundNativeView.h"
#include "ISearchQueryPerformer.h"
#include "ICallback.h"
#include "UpdateNativeModalBackgroundMessage.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace SdkModel
        {
            class ModalBackgroundNativeModalityObserver : private Eegeo::NonCopyable
            {
                ModalBackgroundNativeView& m_modalBackgroundView;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<ModalBackgroundNativeModalityObserver, const Modality::UpdateNativeModalBackgroundMessage&> m_handlerBinding;

                void OnUpdateNativeModalBackgroundMessage(const Modality::UpdateNativeModalBackgroundMessage& message)
                {
                	m_modalBackgroundView.SetFixedOn(message.ShouldFixOn());
                    m_modalBackgroundView.SetAlpha(message.Modality());
                }

            public:
                ModalBackgroundNativeModalityObserver(
                    ModalBackgroundNativeView& modalBackgroundView,
                    ExampleAppMessaging::TMessageBus& messageBus)
                    : m_modalBackgroundView(modalBackgroundView)
                    , m_messageBus(messageBus)
                    , m_handlerBinding(this, &ModalBackgroundNativeModalityObserver::OnUpdateNativeModalBackgroundMessage)
                {
                    m_messageBus.SubscribeNative(m_handlerBinding);
                }

                ~ModalBackgroundNativeModalityObserver()
                {
                    m_messageBus.UnsubscribeNative(m_handlerBinding);
                }
            };
        }
    }
}
