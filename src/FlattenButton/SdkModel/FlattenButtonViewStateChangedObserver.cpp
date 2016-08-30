// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewStateChangedObserver.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            FlattenButtonViewStateChangedObserver::FlattenButtonViewStateChangedObserver(const std::shared_ptr<IFlattenButtonModel>& flattenButtonModel,
                                                                                         const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
                : m_flattenButtonModel(flattenButtonModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &FlattenButtonViewStateChangedObserver::OnFlattenButtonStateChangedMessage)
            {
                m_messageBus->SubscribeNative(m_handlerBinding);
            }

            FlattenButtonViewStateChangedObserver::~FlattenButtonViewStateChangedObserver()
            {
                m_messageBus->UnsubscribeNative(m_handlerBinding);
            }

            void FlattenButtonViewStateChangedObserver::OnFlattenButtonStateChangedMessage(const FlattenButtonViewStateChangedMessage& message)
            {
                if(message.IsFlattened())
                {
                    m_flattenButtonModel->Flatten();
                }
                else
                {
                    m_flattenButtonModel->Unflatten();
                }
            }
        }
    }
}
