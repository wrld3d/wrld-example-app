#pragma once

#include "IIdentity.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReaction
            {
            public:
                virtual Eegeo::Helpers::TIdentity ReactionToOpenableIdentity() = 0;
                virtual void Perform() = 0;
                virtual ~IReaction() { }
            };
        }
    }
}
