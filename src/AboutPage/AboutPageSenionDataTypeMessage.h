// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageSenionDataTypeMessage
        {
            int m_eegeoFloorNumber;
            std::string m_senionFloorId;
            double m_senionLatitude;
            double m_senionLongitude;
            
        public:
            AboutPageSenionDataTypeMessage(int m_eegeoFloorNumber, std::string senionFloorId, double senionLatitude, double senionLongitude);
            
            int32_t GetEegeoFloorNumber() const;
            std::string GetSenionFloorId() const;
            double GetSenionLatitude() const;
            double GetSenionLongitude() const;
        };
    }
}
