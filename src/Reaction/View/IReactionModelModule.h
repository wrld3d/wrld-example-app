// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Reaction.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionModelModule
            {
            public:
                virtual ~IReactionModelModule() { }
                
                virtual IReactionModel& GetReactionModel() const = 0;
            };
        }
    }
}
