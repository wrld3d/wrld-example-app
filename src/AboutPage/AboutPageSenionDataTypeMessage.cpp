// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageSenionDataTypeMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageSenionDataTypeMessage::AboutPageSenionDataTypeMessage(int eeegeoFloorNumber, int32_t senionFloorNumber, double senionLatitude, double senionLongitude)
        : m_eegeoFloorNumber(eeegeoFloorNumber)
        , m_senionFloorNumber(senionFloorNumber)
        , m_sentionLatitude(senionLatitude)
        , m_senionLongitude(senionLongitude)
        {
        }
        
        int32_t AboutPageSenionDataTypeMessage::GetEegeoFloorNumber() const
        {
            return m_eegeoFloorNumber;
        }
        
        int AboutPageSenionDataTypeMessage::GetSenionFloorNumber() const
        {
            return m_senionFloorNumber;
        }
        
        double AboutPageSenionDataTypeMessage::GetSenionLatitude() const
        {
            return m_sentionLatitude;
        }
        
        double AboutPageSenionDataTypeMessage::GetSenionLongitude()const
        {
            return m_senionLongitude;
        }
    }
}
