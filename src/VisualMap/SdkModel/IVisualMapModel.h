// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VisualMapState.h"
#include "ICallback.h"

#include <string>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class IVisualMapModel
            {
            public:
                virtual ~IVisualMapModel(){}
                
                virtual void SetVisualMapState(const VisualMapState& visualMapState, bool storePreviousState) = 0;
                
                virtual VisualMapState GetVisualMapState() const = 0;
                virtual std::string GetTheme() const = 0;
                virtual std::string GetState() const = 0;
                virtual bool IsFlattened() const = 0;
                
                virtual void AddVisualMapStateChangedCallback(Eegeo::Helpers::ICallback2<const VisualMapState&, const bool&>& callback) = 0;
                virtual void RemoveVisualMapStateChangedCallback(Eegeo::Helpers::ICallback2<const VisualMapState&, const bool&>& callback) = 0;
            };
        }
    }
}