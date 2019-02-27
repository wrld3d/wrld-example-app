// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                struct OfflineRoutingGraphBuildResults
                {
                    OfflineRoutingGraphBuildResults(size_t graphSize, size_t averageEdges)
                    : m_graphSize(graphSize)
                    , m_averageEdges(averageEdges)
                    {}

                    const size_t GetGraphSize() const { return m_graphSize; }
                    const size_t GetAverageEdges() const { return m_averageEdges; }

                private:
                    const size_t m_graphSize;
                    const size_t m_averageEdges;
                };
            }
        }
    }
}
