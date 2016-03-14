// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionModel
            {
            public:
                virtual ~IReactionModel() { }

                virtual void AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity) = 0;
                virtual void RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity) = 0;
            };
        }
    }
}
