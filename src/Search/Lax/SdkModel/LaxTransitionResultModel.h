// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorId.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class LaxTransitionResultModel
                {
                private:
                    Eegeo::Resources::Interiors::InteriorId m_targetInteriorId;
                    int m_targetInteriorFloor;
                    Eegeo::Space::LatLong m_targetLatLong;
                    
                public:
                    
                    LaxTransitionResultModel(const Eegeo::Resources::Interiors::InteriorId& targetInteriorId,
                                                 int targetInteriorFloor,
                                                 const Eegeo::Space::LatLong& targetLatLong);
                    
                    LaxTransitionResultModel();
                    
                    ~LaxTransitionResultModel();
                    
                    const Eegeo::Resources::Interiors::InteriorId& GetTargetInteriorId() const;
                    int GetTargetInteriorFloor() const;
                    const Eegeo::Space::LatLong& GetTargetLatLong() const;
                };
            }
        }
    }
}