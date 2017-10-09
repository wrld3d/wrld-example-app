// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowTrainingRoomResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowTrainingRoomResultModel::SwallowTrainingRoomResultModel(const std::string& name,
                                                                       const std::string& officeLocation)
                : m_name(name)
                , m_officeLocation(officeLocation)
                {
                    
                }
                
                SwallowTrainingRoomResultModel::SwallowTrainingRoomResultModel()
                {
                    
                }
                
                SwallowTrainingRoomResultModel::~SwallowTrainingRoomResultModel()
                {
                    
                }
                
                const std::string& SwallowTrainingRoomResultModel::GetName() const
                {
                    return m_name;
                }
                
                const std::string& SwallowTrainingRoomResultModel::GetOfficeLocation() const
                {
                    return m_officeLocation;
                }
            }
        }
    }
}