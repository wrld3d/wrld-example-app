// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowPersonResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowPersonResultModel::SwallowPersonResultModel(const std::string& name,
                                                                   const std::string& jobTitle,
                                                                   const std::string& workingGroup,
                                                                   const std::string& officeLocation,
                                                                   const std::string& deskCode)
                : m_name(name)
                , m_jobTitle(jobTitle)
                , m_workingGroup(workingGroup)
                , m_officeLocation(officeLocation)
                , m_deskCode(deskCode)
                {
                    
                }
                
                SwallowPersonResultModel::SwallowPersonResultModel()
                {
                    
                }
                
                SwallowPersonResultModel::~SwallowPersonResultModel()
                {
                    
                }
                
                const std::string& SwallowPersonResultModel::GetName() const
                {
                    return m_name;
                }
                
                const std::string& SwallowPersonResultModel::GetJobTitle() const
                {
                    return m_jobTitle;
                }
                
                const std::string& SwallowPersonResultModel::GetWorkingGroup() const
                {
                    return m_workingGroup;
                }
                
                const std::string& SwallowPersonResultModel::GetOfficeLocation() const
                {
                    return m_officeLocation;
                }
                
                const std::string& SwallowPersonResultModel::GetDeskCode() const
                {
                    return m_deskCode;
                }
            }
        }
    }
}