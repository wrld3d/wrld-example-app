// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModeSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingModeSetMessage::NavRoutingModeSetMessage(const SdkModel::NavRoutingMode navMode)
        : m_navMode(navMode)
        {

        }

        SdkModel::NavRoutingMode NavRoutingModeSetMessage::GetNavMode() const
        {
            return m_navMode;
        }
    }
}
