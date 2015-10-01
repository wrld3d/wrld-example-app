// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowMeetingRoomResultModel
                {
                private:
                    std::string m_name;
                    std::string m_imageUrl;
                    std::string m_availability;
                    
                public:
                    
                    SwallowMeetingRoomResultModel(const std::string& name,
                                                  const std::string& imageUrl,
                                                  const std::string& availability);
                    
                    SwallowMeetingRoomResultModel();
                    
                    ~SwallowMeetingRoomResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetImageUrl() const;
                    
                    const std::string& GetAvailability() const;
                };
            }
        }
    }
}