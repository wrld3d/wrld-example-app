// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "INavRoutingModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingCurrentDirectionSetMessage
        {
        private:
            int m_directionIndex;

        public:
            NavRoutingCurrentDirectionSetMessage(int directionIndex);

            int GetDirectionIndex() const;
        };
    }
}
