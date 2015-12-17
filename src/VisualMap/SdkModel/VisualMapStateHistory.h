// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IVisualMapStateHistory.h"
#include "VisualMapState.h"

#include "Types.h"

#include <list>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapStateHistory : public IVisualMapStateHistory, protected Eegeo::NonCopyable
            {
            public:
                VisualMapStateHistory();
                
                void Push(const VisualMapState& visualMapState);
                VisualMapState Pop();
            
            private:
                std::list<VisualMapState> m_entries;
            };
        }
    }
}