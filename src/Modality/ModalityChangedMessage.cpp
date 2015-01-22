// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalityChangedMessage.h"

namespace ExampleApp
{
    namespace Modality
    {
        ModalityChangedMessage::ModalityChangedMessage(float modality)
            : m_modality(modality)
        {

        }

        float ModalityChangedMessage::Modality() const
        {
            return m_modality;
        }
    }
}
