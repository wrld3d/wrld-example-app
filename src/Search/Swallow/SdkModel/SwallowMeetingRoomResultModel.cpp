// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowMeetingRoomResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowMeetingRoomResultModel::SwallowMeetingRoomResultModel(const std::string& name,
                                                                             const std::string& imageUrl,
                                                                             const std::string& availability,
                                                                             const std::string& officeLocation)
                : m_name(name)
                , m_imageUrl(imageUrl)
                , m_availability(availability)
                , m_officeLocation(officeLocation)
                {
                    
                }
                
                SwallowMeetingRoomResultModel::SwallowMeetingRoomResultModel()
                {
                    
                }
                
                SwallowMeetingRoomResultModel::~SwallowMeetingRoomResultModel()
                {
                    
                }
                
                const std::string& SwallowMeetingRoomResultModel::GetName() const
                {
                    return m_name;
                }
                
                const std::string& SwallowMeetingRoomResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                const std::string& SwallowMeetingRoomResultModel::GetAvailability() const
                {
                    return m_availability;
                }
                
                const std::string& SwallowMeetingRoomResultModel::GetOfficeLocation() const
                {
                    return m_officeLocation;
                }
            }
        }
    }
}