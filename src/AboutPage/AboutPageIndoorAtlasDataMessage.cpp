// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageSenionDataMessage.h"
#include "AboutPageIndoorAtlasDataMessage.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageIndoorAtlasDataMessage::AboutPageIndoorAtlasDataMessage(int eeegeoFloorIndex,
                                                                         std::string indoorAtlasFloorId,
                                                                         double latitude,
                                                                         double longitude)
        : m_eegeoFloorIndex(eeegeoFloorIndex)
        , m_indoorAtlasFloorId(indoorAtlasFloorId)
        , m_latitude(latitude)
        , m_longitude(longitude)
        {
        }
        
        int32_t AboutPageIndoorAtlasDataMessage::GetEegeoFloorIndex() const
        {
            return m_eegeoFloorIndex;
        }
        
        std::string AboutPageIndoorAtlasDataMessage::GetIndoorAtlasFloorId() const
        {
            return m_indoorAtlasFloorId;
        }
        
        double AboutPageIndoorAtlasDataMessage::GetLatitude() const
        {
            return m_latitude;
        }
        
        double AboutPageIndoorAtlasDataMessage::GetLongitude()const
        {
            return m_longitude;
        }
    }
}
