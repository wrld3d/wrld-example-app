// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerFloorSelectedMessage
        {
        public:
            InteriorsExplorerFloorSelectedMessage(int floorIndex,
                                                  const std::string& floorName)
            : m_floorIndex(floorIndex)
            , m_floorName(floorName)
            {
            }
            
            const int GetFloorIndex() const { return m_floorIndex; }
            std::string GetFloorName() const { return m_floorName; }
            
        private:
            int m_floorIndex;
            std::string m_floorName;
        };
    }
}