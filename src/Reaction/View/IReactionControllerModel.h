// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IIdentity.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionControllerModel
            {
            public:
                virtual ~IReactionControllerModel() { }

                virtual bool IsAnyOpenableOpen() const = 0;

                virtual bool IsOpenableOpen(Eegeo::Helpers::TIdentity identity) const = 0;

                virtual bool IsModalControlAcquired() const = 0;

                virtual bool HasModalControl(Eegeo::Helpers::TIdentity identity) const = 0;
            };
        }
    }
}
