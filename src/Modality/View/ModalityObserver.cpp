// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityObserver.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            ModalityObserver::ModalityObserver(IModalityModel& modalityModel,
                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_modalityModel(modalityModel)
                , m_messageBus(messageBus)
                , m_modalityChangedCallback(this, &ModalityObserver::HandleModalityChanged)
            {
                m_modalityModel.InsertModalityChangedCallback(m_modalityChangedCallback);
            }

            ModalityObserver::~ModalityObserver()
            {
                m_modalityModel.RemoveModalityChangedCallback(m_modalityChangedCallback);
            }

            void ModalityObserver::HandleModalityChanged()
            {
                m_messageBus.Publish(ModalityChangedMessage(m_modalityModel.GetModality()));
            }
        }
    }
}
