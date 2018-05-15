// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "INavRoutingModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingSelectedDirectionChangedMessage
        {
        private:
            int m_directionIndex;

        public:
            NavRoutingSelectedDirectionChangedMessage(int directionIndex);

            int GetDirectionIndex() const;
        };
    }
}
