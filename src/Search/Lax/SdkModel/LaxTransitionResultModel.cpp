// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxTransitionResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxTransitionResultModel::LaxTransitionResultModel(const Eegeo::Resources::Interiors::InteriorId& targetInteriorID,
                                                                           int targetInteriorFloor,
                                                                           const Eegeo::Space::LatLong& targetLatLong)
                : m_targetInteriorId(targetInteriorID)
                , m_targetInteriorFloor(targetInteriorFloor)
                , m_targetLatLong(targetLatLong)
                {
                    
                }
                
                LaxTransitionResultModel::LaxTransitionResultModel()
                : m_targetInteriorId("")
                , m_targetInteriorFloor(0)
                , m_targetLatLong(Eegeo::Space::LatLong::FromDegrees(0.0, 0.0))
                {
                    
                }
                
                LaxTransitionResultModel::~LaxTransitionResultModel()
                {
                    
                }
                
                const Eegeo::Resources::Interiors::InteriorId& LaxTransitionResultModel::GetTargetInteriorId() const
                {
                    return  m_targetInteriorId;
                }
                
                int LaxTransitionResultModel::GetTargetInteriorFloor() const
                {
                    return m_targetInteriorFloor;
                }
                
                const Eegeo::Space::LatLong& LaxTransitionResultModel::GetTargetLatLong() const
                {
                    return m_targetLatLong;
                }
            }
        }
    }
}