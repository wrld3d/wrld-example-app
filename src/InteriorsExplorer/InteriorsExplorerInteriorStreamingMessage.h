// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerInteriorStreamingMessage
        {
        public:
            InteriorsExplorerInteriorStreamingMessage(bool interiorStreaming)
            : m_interiorStreaming(interiorStreaming)
            {
            }
            
            const bool GetInteriorStreaming() const { return m_interiorStreaming; }
            
        private:
            bool m_interiorStreaming;
        };
    }
}
