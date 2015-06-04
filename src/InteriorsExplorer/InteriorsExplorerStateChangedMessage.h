// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerStateChangedMessage
        {
        public:
            InteriorsExplorerStateChangedMessage(bool interiorVisible,
                                                 int floorCount,
                                                 int floor)
            : m_interiorVisible(interiorVisible)
            , m_floorCount(floorCount)
            , m_floor(floor)
            {
            }
            
            const bool IsInteriorVisible() const { return m_interiorVisible; }
            const int GetFloorCount() const { return m_floorCount; }
            const int GetCurrentlySelectedFloor() const { return m_floor; }
            
        private:
            bool m_interiorVisible;
            int m_floorCount;
            int m_floor;
        };
    }
}