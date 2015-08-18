// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPinsSetScaleMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        InteriorPinsSetScaleMessage::InteriorPinsSetScaleMessage(float scale)
        : m_scale(scale)
        {

        }

        float InteriorPinsSetScaleMessage::GetScale() const
        {
            return m_scale;
        }
    }
}