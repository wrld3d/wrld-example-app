// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageIndoorPositionTypeMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageIndoorPositionTypeMessage::AboutPageIndoorPositionTypeMessage(std::string indoorPositioningType)
        : m_indoorPositioningType(std::move(indoorPositioningType))
        {
        }
        
        std::string AboutPageIndoorPositionTypeMessage::GetIndoorPositioningType() const
        {
            return m_indoorPositioningType;
        }
    }
}
