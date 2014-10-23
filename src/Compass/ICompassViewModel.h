// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Compass
    {
        class ICompassViewModel : public ScreenControlViewModel::IScreenControlViewModel
        {
        public:
            virtual ~ICompassViewModel() { }
            
            virtual void UpdateHeadingAngleRadians(float headingRadians) = 0;
            
            virtual void InsertUpdateCallback(Eegeo::Helpers::ICallback1<float>& updateCallback) = 0;
            
            virtual void RemoveUpdateCallback(Eegeo::Helpers::ICallback1<float>& updateCallback) = 0;
        };
    }
}
