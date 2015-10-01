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
                class SwallowPersonResultModel
                {
                private:
                    std::string m_name;
                    std::string m_jobTitle;
                    std::string m_imageFilename;
                    std::string m_workingGroup;
                    std::string m_officeLocation;
                    std::string m_deskCode;
                    
                public:
                    
                    SwallowPersonResultModel(const std::string& name,
                                             const std::string& jobTitle,
                                             const std::string& imageFilename,
                                             const std::string& workingGroup,
                                             const std::string& officeLocation,
                                             const std::string& deskCode);
                    
                    SwallowPersonResultModel();
                    
                    ~SwallowPersonResultModel();
                    
                    const std::string& GetName() const;
                    
                    const std::string& GetJobTitle() const;
                    
                    const std::string& GetImageFilename() const;
                    
                    const std::string& GetWorkingGroup() const;
                    
                    const std::string& GetOfficeLocation() const;
                    
                    const std::string& GetDeskCode() const;
                };
            }
        }
    }
}