// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxMeetingRoomResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxMeetingRoomResultModel::LaxMeetingRoomResultModel(const std::string& name,
                                                                             const std::string& imageUrl,
                                                                             const std::string& availability)
                : m_name(name)
                , m_imageUrl(imageUrl)
                , m_availability(availability)
                {
                    
                }
                
                LaxMeetingRoomResultModel::LaxMeetingRoomResultModel()
                {
                    
                }
                
                LaxMeetingRoomResultModel::~LaxMeetingRoomResultModel()
                {
                    
                }
                
                const std::string& LaxMeetingRoomResultModel::GetName() const
                {
                    return m_name;
                }
                
                const std::string& LaxMeetingRoomResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                const std::string& LaxMeetingRoomResultModel::GetAvailability() const
                {
                    return m_availability;
                }
            }
        }
    }
}