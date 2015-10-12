// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsVisibilityMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinsVisibilityMessage::WorldPinsVisibilityMessage(int visibilityMask)
            : m_setVisible(visibilityMask != 0)
            , m_visibilityMask(visibilityMask)
        {
        }
    }
}