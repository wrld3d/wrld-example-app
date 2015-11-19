// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorId.h"
#include <string>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorsExplorerEnteredMessage
        {
        public:
            InteriorsExplorerEnteredMessage(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            : m_interiorId(interiorId)
            {
            }
            
            Eegeo::Resources::Interiors::InteriorId GetInteriorId() const { return m_interiorId; }
            
        private:
            const Eegeo::Resources::Interiors::InteriorId m_interiorId;
        };
    }
}