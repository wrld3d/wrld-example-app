// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowDeskGroupResultModel
                {
                private:
                    std::string m_name;
                    std::vector<std::string> m_desks;
                    
                public:
                    
                    SwallowDeskGroupResultModel(const std::string& name,
                                                const std::vector<std::string>& desks);
                    
                    SwallowDeskGroupResultModel();
                    
                    ~SwallowDeskGroupResultModel();
                    
                    const std::string& GetName() const;

                    const std::vector<std::string>& GetAllDesks() const;
                };
            }
        }
    }
}