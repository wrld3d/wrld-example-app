// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class IModalBackgroundView
            {
            public:
                virtual ~IModalBackgroundView() {};

                virtual void SetFullyActive() = 0;
                virtual void SetFullyInactive() = 0;
                virtual void SetActiveStateToIntermediateValue(float modality) = 0;
            };
        }
    }
}
