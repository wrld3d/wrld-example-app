// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerStateChangedMessage
        {
        public:
            InteriorsExplorerStateChangedMessage(bool interiorVisible,
                                                 int selectedFloor,
                                                 const std::string& floorName,
                                                 const std::vector<int>& floorNumbers)
            : m_interiorVisible(interiorVisible)
            , m_selectedFloor(selectedFloor)
            , m_floorName(floorName)
            , m_floorNumbers(floorNumbers)
            {
            }
            
            const bool IsInteriorVisible() const { return m_interiorVisible; }
            int GetSelectedFloor() const { return m_selectedFloor; }
            std::string GetFloorName() const { return m_floorName; }
            const std::vector<int>& GetFloorNumbers() const { return m_floorNumbers; }
            
        private:
            bool m_interiorVisible;
            int m_selectedFloor;
            std::string m_floorName;
            std::vector<int> m_floorNumbers;
        };
    }
}