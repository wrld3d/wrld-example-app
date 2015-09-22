// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        class TourChangeRequestMessage
        {
            std::string m_tourName;
            
        public:
            TourChangeRequestMessage(const std::string& tourName);
            
            const std::string GetTourName() const;
        };
    }
}
