// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Reaction.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionControllerModule
            {
            public:
                virtual ~IReactionControllerModule() { }

                virtual IReactionControllerModel& GetReactionControllerModel() const = 0;
            };
        }
    }
}
