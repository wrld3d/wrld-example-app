// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UpdateNativeModalBackgroundMessage.h"

namespace ExampleApp
{
    namespace Modality
    {
        UpdateNativeModalBackgroundMessage::UpdateNativeModalBackgroundMessage(float modality, bool fixed)
            : m_modality(modality)
        	, m_fixed(fixed)
        {

        }

        float UpdateNativeModalBackgroundMessage::Modality() const
        {
            return m_modality;
        }

        bool UpdateNativeModalBackgroundMessage::ShouldFixOn() const
        {
        	return m_fixed;
        }
    }
}
