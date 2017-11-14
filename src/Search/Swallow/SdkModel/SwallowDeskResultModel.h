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
                class SwallowDeskResultModel
                {
                private:
                    std::string m_employeeName;
                    std::string m_employeeSubtitle;
                    std::string m_imageFilename;
                    std::string m_workingGroup;
                    std::string m_officeLocation;
                    std::string m_deskCode;
                    
                public:
                    
                    SwallowDeskResultModel(const std::string& employeeName,
                                             const std::string& employeeSubtitle,
                                             const std::string& imageFilename,
                                             const std::string& workingGroup,
                                             const std::string& officeLocation,
                                             const std::string& deskCode);
                    
                    SwallowDeskResultModel();
                    
                    ~SwallowDeskResultModel();
                    
                    const std::string& GetEmployeeName() const;
                    
                    const std::string& GetEmployeeSubtitle() const;
                    
                    const std::string& GetImageFilename() const;
                    
                    const std::string& GetWorkingGroup() const;
                    
                    const std::string& GetOfficeLocation() const;
                    
                    const std::string& GetDeskCode() const;
                };
            }
        }
    }
}
