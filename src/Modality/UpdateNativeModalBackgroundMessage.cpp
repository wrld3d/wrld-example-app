// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UpdateNativeModalBackgroundMessage.h"

namespace ExampleApp
{
    namespace Modality
    {
        UpdateNativeModalBackgroundMessage::UpdateNativeModalBackgroundMessage(float modality)
            : m_modality(modality)
        {

        }

        float UpdateNativeModalBackgroundMessage::Modality() const
        {
            return m_modality;
        }
    }
}
