// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingModeSetMessage
        {
        private:
            SdkModel::NavRoutingMode m_navMode;

        public:
            NavRoutingModeSetMessage(const SdkModel::NavRoutingMode navMode);

            SdkModel::NavRoutingMode GetNavMode() const;
        };
    }
}
