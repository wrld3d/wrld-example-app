// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowTransitionResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowTransitionResultModel::SwallowTransitionResultModel(const Eegeo::Resources::Interiors::InteriorId& targetInteriorID,
                                                                           int targetInteriorFloor,
                                                                           const Eegeo::Space::LatLong& targetLatLong)
                : m_targetInteriorId(targetInteriorID)
                , m_targetInteriorFloor(targetInteriorFloor)
                , m_targetLatLong(targetLatLong)
                {
                    
                }
                
                SwallowTransitionResultModel::SwallowTransitionResultModel()
                : m_targetInteriorId("")
                , m_targetInteriorFloor(0)
                , m_targetLatLong(Eegeo::Space::LatLong::FromDegrees(0.0, 0.0))
                {
                    
                }
                
                SwallowTransitionResultModel::~SwallowTransitionResultModel()
                {
                    
                }
                
                const Eegeo::Resources::Interiors::InteriorId& SwallowTransitionResultModel::GetTargetInteriorId() const
                {
                    return  m_targetInteriorId;
                }
                
                int SwallowTransitionResultModel::GetTargetInteriorFloor() const
                {
                    return m_targetInteriorFloor;
                }
                
                const Eegeo::Space::LatLong& SwallowTransitionResultModel::GetTargetLatLong() const
                {
                    return m_targetLatLong;
                }
            }
        }
    }
}