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
                class SwallowTrainingRoomResultModel
                {
                private:
                    std::string m_name;
                    std::string m_officeLocation;
                    
                public:
                    
                    SwallowTrainingRoomResultModel(const std::string& name,
                                                   const std::string& officeLocation);
                    
                    SwallowTrainingRoomResultModel();
                    
                    ~SwallowTrainingRoomResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetOfficeLocation() const;
                };
            }
        }
    }
}