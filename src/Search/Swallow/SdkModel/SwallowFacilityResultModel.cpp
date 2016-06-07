// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowFacilityResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowFacilityResultModel::SwallowFacilityResultModel(const std::string& name,
                                                                       const std::string& imageUrl,
                                                                       const std::string& description,
                                                                       const std::string& officeLocation)
                : m_name(name)
                , m_imageUrl(imageUrl)
                , m_description(description)
                , m_officeLocation(officeLocation)
                {
                    
                }
                
                SwallowFacilityResultModel::SwallowFacilityResultModel()
                {
                    
                }
                
                SwallowFacilityResultModel::~SwallowFacilityResultModel()
                {
                    
                }
                
                const std::string& SwallowFacilityResultModel::GetName() const
                {
                    return m_name;
                }
                
                const std::string& SwallowFacilityResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                const std::string& SwallowFacilityResultModel::GetDescription() const
                {
                    return m_description;
                }
                
                const std::string& SwallowFacilityResultModel::GetOfficeLocation() const
                {
                    return m_officeLocation;
                }
            }
        }
    }
}