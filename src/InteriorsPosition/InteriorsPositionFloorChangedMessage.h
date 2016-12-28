// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsPositionFloorChangedMessage
        {
        public:
        	InteriorsPositionFloorChangedMessage(int floorIndex)
            : m_floorIndex(floorIndex)
            {
            }
            
        	int GetFloorIndex() const { return m_floorIndex; }
            
        private:
            int m_floorIndex;
        };
    }
}
