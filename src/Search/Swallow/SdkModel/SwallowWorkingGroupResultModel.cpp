// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowWorkingGroupResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowWorkingGroupResultModel::SwallowWorkingGroupResultModel(const std::string& name,
                                                                               const std::string& imageUrl,
                                                                               const std::string& description,
                                                                               const std::string& officeLocation)
                : m_name(name)
                , m_imageUrl(imageUrl)
                , m_description(description)
                , m_officeLocation(officeLocation)
                {
                    
                }
                
                SwallowWorkingGroupResultModel::SwallowWorkingGroupResultModel()
                {
                    
                }
                
                SwallowWorkingGroupResultModel::~SwallowWorkingGroupResultModel()
                {
                    
                }
                
                const std::string& SwallowWorkingGroupResultModel::GetName() const
                {
                    return m_name;
                }
                
                const std::string& SwallowWorkingGroupResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                const std::string& SwallowWorkingGroupResultModel::GetDescription() const
                {
                    return m_description;
                }
                
                const std::string& SwallowWorkingGroupResultModel::GetOfficeLocation() const
                {
                    return m_officeLocation;
                }
            }
        }
    }
}