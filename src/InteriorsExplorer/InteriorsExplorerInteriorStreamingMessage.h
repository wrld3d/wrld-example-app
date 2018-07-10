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
                , m_interiorLoaded(false)
            {
            }

            InteriorsExplorerInteriorStreamingMessage(bool interiorStreaming, bool interiorLoaded)
                : m_interiorStreaming(interiorStreaming)
                , m_interiorLoaded(interiorLoaded)
            {
            }

            const bool GetInteriorStreaming() const { return m_interiorStreaming; }
            const bool GetInteriorLoaded() const { return m_interiorLoaded; }
            
        private:
            bool m_interiorStreaming;
            bool m_interiorLoaded;
        };
    }
}
