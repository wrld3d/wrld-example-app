// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Watermark.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            class IWatermarkModule
            {
            public:
                virtual ~IWatermarkModule() { }
                
                virtual View::IWatermarkViewModel& GetWatermarkViewModel() const = 0;
                
                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
                
                virtual View::IWatermarkDataRepository& GetWatermarkDataRepository() const = 0;
                
                virtual View::IWatermarkDataFactory& GetWatermarkDataFactory() const = 0;
            };
        }
    }
}
