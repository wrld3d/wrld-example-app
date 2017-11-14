// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowDeskResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowDeskResultModel::SwallowDeskResultModel(const std::string& employeeName,
                                                                   const std::string& employeeSubtitle,
                                                                   const std::string& imageFilename,
                                                                   const std::string& workingGroup,
                                                                   const std::string& officeLocation,
                                                                   const std::string& deskCode)
                : m_employeeName(employeeName)
                , m_employeeSubtitle(employeeSubtitle)
                , m_imageFilename(imageFilename)
                , m_workingGroup(workingGroup)
                , m_officeLocation(officeLocation)
                , m_deskCode(deskCode)
                {
                    
                }
                
                SwallowDeskResultModel::SwallowDeskResultModel()
                {
                    
                }
                
                SwallowDeskResultModel::~SwallowDeskResultModel()
                {
                    
                }
                
                const std::string& SwallowDeskResultModel::GetEmployeeName() const
                {
                    return m_employeeName;
                }
                
                const std::string& SwallowDeskResultModel::GetEmployeeSubtitle() const
                {
                    return m_employeeSubtitle;
                }
                
                const std::string& SwallowDeskResultModel::GetImageFilename() const
                {
                    return m_imageFilename;
                }
                
                const std::string& SwallowDeskResultModel::GetWorkingGroup() const
                {
                    return m_workingGroup;
                }
                
                const std::string& SwallowDeskResultModel::GetOfficeLocation() const
                {
                    return m_officeLocation;
                }
                
                const std::string& SwallowDeskResultModel::GetDeskCode() const
                {
                    return m_deskCode;
                }
            }
        }
    }
}
