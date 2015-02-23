// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RepositoryModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class IModalityModel
            {
            public:
                virtual ~IModalityModel() { }

                virtual bool IsModalEnabled() const = 0;

                virtual float GetModality() const = 0;

                virtual void SetModality(float modality) = 0;

                virtual void InsertModalityChangedCallback(Eegeo::Helpers::ICallback0& modalityChangedCallback) = 0;

                virtual void RemoveModalityChangedCallback(Eegeo::Helpers::ICallback0& modalityChangedCallback) = 0;
            };
        }
    }
}
