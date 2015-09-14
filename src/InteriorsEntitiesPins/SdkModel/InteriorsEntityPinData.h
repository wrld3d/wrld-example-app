// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

namespace ExampleApp
{
    namespace InteriorsEntitiesPins
    {
        namespace SdkModel
        {
            namespace Entities
            {
                class InteriorsEntityPinData : private Eegeo::NonCopyable
                {
                public:
                    InteriorsEntityPinData(int floorNumber)
                    : m_floorNumber(floorNumber)
                    {
                        
                    }
                    
                    int GetFloorNumber() const { return m_floorNumber; }
                    
                private:
                    int m_floorNumber;
                };
            }
        }
    }
}