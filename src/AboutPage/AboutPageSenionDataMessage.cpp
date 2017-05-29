// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageSenionDataMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageSenionDataMessage::AboutPageSenionDataMessage(int eeegeoFloorNumber, int32_t senionFloorNumber, double senionLatitude, double senionLongitude)
        : m_eegeoFloorNumber(eeegeoFloorNumber)
        , m_senionFloorNumber(senionFloorNumber)
        , m_sentionLatitude(senionLatitude)
        , m_senionLongitude(senionLongitude)
        {
        }
        
        int32_t AboutPageSenionDataMessage::GetEegeoFloorNumber() const
        {
            return m_eegeoFloorNumber;
        }
        
        int AboutPageSenionDataMessage::GetSenionFloorNumber() const
        {
            return m_senionFloorNumber;
        }
        
        double AboutPageSenionDataMessage::GetSenionLatitude() const
        {
            return m_sentionLatitude;
        }
        
        double AboutPageSenionDataMessage::GetSenionLongitude()const
        {
            return m_senionLongitude;
        }
    }
}
