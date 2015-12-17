// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VisualMapStateHistory.h"
#include "Types.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            namespace
            {
                const size_t MaxEntries = 20;
            }
            
            VisualMapStateHistory::VisualMapStateHistory()
            {
            }
            
            void VisualMapStateHistory::Push(const VisualMapState& visualMapState)
            {
                m_entries.push_back(visualMapState);
                
                if (m_entries.size() > MaxEntries)
                {
                    m_entries.erase(m_entries.begin());
                }
            }
            
            VisualMapState VisualMapStateHistory::Pop()
            {
                Eegeo_ASSERT(!m_entries.empty(), "Trying to pop empty VisualMapStateHistory");
                VisualMapState mostRecent = m_entries.back();
                
                m_entries.pop_back();
                
                return mostRecent;
            }
        }
    }
}