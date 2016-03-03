// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerFloorSelectionDraggedMessage
        {
        public:
            InteriorsExplorerFloorSelectionDraggedMessage(float dragParameter)
            : m_dragParam(dragParameter)
            {
            }
            
            const float GetDragParam() const { return m_dragParam; }
            
        private:
            float m_dragParam;
        };
    }
}