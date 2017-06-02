// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageSenionDataMessage
        {
            int m_eegeoFloorNumber;
            int32_t m_senionFloorNumber;
            double m_sentionLatitude;
            double m_senionLongitude;
            
        public:
            AboutPageSenionDataMessage(int m_eegeoFloorNumber, int32_t senionFloorNumber, double senionLatitude, double senionLongitude);
            
            int32_t GetEegeoFloorNumber() const;
            int GetSenionFloorNumber() const;
            double GetSenionLatitude() const;
            double GetSenionLongitude() const;
        };
    }
}
