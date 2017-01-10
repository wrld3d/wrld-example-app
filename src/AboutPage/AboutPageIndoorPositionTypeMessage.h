// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageIndoorPositionTypeMessage
        {
            std::string m_indoorPositioningType;
            
        public:
            AboutPageIndoorPositionTypeMessage(std::string indoorPositioningType);
            
            std::string GetIndoorPositioningType() const;
        };
    }
}
