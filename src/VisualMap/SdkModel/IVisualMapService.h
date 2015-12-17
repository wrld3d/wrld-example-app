// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VisualMap.h"

#include <string>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class IVisualMapService
            {
            public:
                virtual ~IVisualMapService() {}
                
                virtual void SetVisualMapState(const VisualMapState& visualMapState) = 0;
                virtual void SetVisualMapState(const std::string& theme, const std::string& state, bool isFlattened) = 0;
                
                virtual void SetVisualMapTheme(const std::string& theme) = 0;
                virtual void SetVisualMapThemeState(const std::string& state) = 0;
                virtual void SetVisualMapFlattenedState(bool isFlattened) = 0;
                
                virtual VisualMapState GetCurrentVisualMapState() const = 0;
                
                virtual void StoreCurrentMapState() = 0;
                virtual void RestorePreviousMapState() = 0;
            };
        }
    }
}