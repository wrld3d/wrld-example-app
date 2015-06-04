// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerFloorSelectedMessage
        {
        public:
            InteriorsExplorerFloorSelectedMessage(int floor)
            : m_floor(floor)
            {
            }
            
            const int GetFloor() const { return m_floor; }
            
        private:
            int m_floor;
        };
    }
}