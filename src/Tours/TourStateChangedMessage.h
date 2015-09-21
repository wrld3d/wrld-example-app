// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        class TourStateChangedMessage
        {
            bool m_tourStarted;
        
        public:
            TourStateChangedMessage(bool tourStarted);
        
            const bool TourStarted() const;
        };
    }
}