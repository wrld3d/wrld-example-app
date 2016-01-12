// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IVisualMapService.h"
#include "VisualMap.h"

#include "Types.h"

#include <string>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapService : public IVisualMapService, protected Eegeo::NonCopyable
            {
            public:
                VisualMapService(IVisualMapModel& visualMapModel,
                                 IVisualMapStateHistory& visualMapStateHistory);
                
                void SetVisualMapState(const VisualMapState& visualMapState);
                void SetVisualMapState(const std::string& theme, const std::string& state, bool isFlattened);
                
                void SetVisualMapTheme(const std::string& theme);
                void SetVisualMapThemeState(const std::string& state);
                void SetVisualMapFlattenedState(bool isFlattened);
                
                VisualMapState GetCurrentVisualMapState() const;
            
                void StoreCurrentMapState();
                void RestorePreviousMapState();
                
            private:
                IVisualMapModel& m_visualMapModel;
                IVisualMapStateHistory& m_visualMapStateHistory;
            };
        }
    }
}