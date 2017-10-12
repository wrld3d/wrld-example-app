// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageSenionDataTypeMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageSenionDataTypeMessage::AboutPageSenionDataTypeMessage(int eeegeoFloorNumber, std::string senionFloorId, double senionLatitude, double senionLongitude)
        : m_eegeoFloorNumber(eeegeoFloorNumber)
        , m_senionFloorId(senionFloorId)
        , m_senionLatitude(senionLatitude)
        , m_senionLongitude(senionLongitude)
        {
        }
        
        int32_t AboutPageSenionDataTypeMessage::GetEegeoFloorNumber() const
        {
            return m_eegeoFloorNumber;
        }
        
        std::string AboutPageSenionDataTypeMessage::GetSenionFloorId() const
        {
            return m_senionFloorId;
        }
        
        double AboutPageSenionDataTypeMessage::GetSenionLatitude() const
        {
            return m_senionLatitude;
        }
        
        double AboutPageSenionDataTypeMessage::GetSenionLongitude()const
        {
            return m_senionLongitude;
        }
    }
}
