// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

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
                
                virtual void InsertTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
