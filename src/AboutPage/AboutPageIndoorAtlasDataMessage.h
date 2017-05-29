// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageIndoorAtlasDataMessage
        {
            int m_eegeoFloorIndex;
            std::string m_indoorAtlasFloorId;
            double m_latitude;
            double m_longitude;
            
        public:
            AboutPageIndoorAtlasDataMessage(int eegeoFloorIndex,
                                            std::string indoorAtlasFloorId,
                                            double latitude,
                                            double longitude);
            
            int32_t GetEegeoFloorIndex() const;
            std::string GetIndoorAtlasFloorId() const;
            double GetLatitude() const;
            double GetLongitude() const;
        };
    }
}
