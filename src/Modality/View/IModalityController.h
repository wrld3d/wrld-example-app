// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class IModalityController
            {
            public:
                virtual ~IModalityController() { }

                virtual void AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity) = 0;
                virtual void RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity) = 0;
            };
        }
    }
}
