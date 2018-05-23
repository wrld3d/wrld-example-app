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
            typedef bool ModalityValue;
            class IModalityModel
            {
            public:
                virtual ~IModalityModel() { }

                virtual ModalityValue GetModality() const = 0;

                virtual void SetModality(ModalityValue modality) = 0;

                virtual void InsertModalityChangedCallback(Eegeo::Helpers::ICallback0& modalityChangedCallback) = 0;

                virtual void RemoveModalityChangedCallback(Eegeo::Helpers::ICallback0& modalityChangedCallback) = 0;
            };
        }
    }
}
