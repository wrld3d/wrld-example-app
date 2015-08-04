// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            class IMapModeModel
            {
            public:
                virtual ~IMapModeModel()
                {

                }

                virtual bool IsInMapMode() const = 0;
                virtual void SetInMapMode(bool inMapMode) = 0;

                virtual void AddMapModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveMapModeChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}