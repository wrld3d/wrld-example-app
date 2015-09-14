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
                                                 int selectedFloorIndex,
                                                 const std::string& selectedFloorName,
                                                 const std::vector<std::string>& floorShortNames)
            : m_interiorVisible(interiorVisible)
            , m_selectedFloorIndex(selectedFloorIndex)
            , m_selectedFloorName(selectedFloorName)
            , m_floorShortNames(floorShortNames)
            {
            }
            
            bool IsInteriorVisible() const { return m_interiorVisible; }
            int GetSelectedFloorIndex() const { return m_selectedFloorIndex; }
            std::string GetSelectedFloorName() const { return m_selectedFloorName; }
            std::vector<std::string> GetFloorShortNames() const { return m_floorShortNames; }
            
        private:
            const bool m_interiorVisible;
            const int m_selectedFloorIndex;
            const std::string m_selectedFloorName;
            const std::vector<std::string> m_floorShortNames;
        };
    }
}