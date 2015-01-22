// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            class IFlattenButtonModel
            {
            public:

                virtual ~IFlattenButtonModel() {}

                virtual void Flatten() = 0;

                virtual void Unflatten() = 0;

                virtual bool GetFlattened() const = 0;

                virtual void InsertChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void RemoveChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
