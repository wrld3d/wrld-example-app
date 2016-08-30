// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonModelStateChangedObserver.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            FlattenButtonModelStateChangedObserver::FlattenButtonModelStateChangedObserver(const std::shared_ptr<IFlattenButtonModel>& flattenButtonModel,
                                                                                           const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
                : m_flattenButtonModel(flattenButtonModel)
                , m_messageBus(messageBus)
                , m_flattenStateChangedCallback(this, &FlattenButtonModelStateChangedObserver::HandleFlattenStateChanged)
            {
                m_flattenButtonModel->InsertChangedCallback(m_flattenStateChangedCallback);
            }

            FlattenButtonModelStateChangedObserver::~FlattenButtonModelStateChangedObserver()
            {
                m_flattenButtonModel->RemoveChangedCallback(m_flattenStateChangedCallback);
            }

            void FlattenButtonModelStateChangedObserver::HandleFlattenStateChanged()
            {
                m_messageBus->Publish(FlattenButtonModelStateChangedMessage(m_flattenButtonModel->GetFlattened()));
            }
        }
    }
}
