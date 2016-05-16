// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <vector>
#include "IIdentity.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuIgnoredReactionModel
            {
            public:
                virtual ~IMenuIgnoredReactionModel() {};

                virtual void AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity) = 0;
                virtual bool RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity) = 0;

                virtual bool IsIgnored(Eegeo::Helpers::TIdentity) const = 0;
            };
        }
    }
}
