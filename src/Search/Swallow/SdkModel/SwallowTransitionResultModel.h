// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorId.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowTransitionResultModel
                {
                private:
                    Eegeo::Resources::Interiors::InteriorId m_targetInteriorId;
                    int m_targetInteriorFloor;
                    Eegeo::Space::LatLong m_targetLatLong;
                    
                public:
                    
                    SwallowTransitionResultModel(const Eegeo::Resources::Interiors::InteriorId& targetInteriorId,
                                                 int targetInteriorFloor,
                                                 const Eegeo::Space::LatLong& targetLatLong);
                    
                    SwallowTransitionResultModel();
                    
                    ~SwallowTransitionResultModel();
                    
                    const Eegeo::Resources::Interiors::InteriorId& GetTargetInteriorId() const;
                    int GetTargetInteriorFloor() const;
                    const Eegeo::Space::LatLong& GetTargetLatLong() const;
                };
            }
        }
    }
}