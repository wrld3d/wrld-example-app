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
                VisualMapService(const std::shared_ptr<IVisualMapModel>& visualMapModel,
                                 const std::shared_ptr<IVisualMapStateHistory>& visualMapStateHistory);
                
                void SetVisualMapState(const VisualMapState& visualMapState);
                void SetVisualMapState(const std::string& theme, const std::string& state, bool isFlattened);
                
                void SetVisualMapTheme(const std::string& theme);
                void SetVisualMapThemeState(const std::string& state);
                void SetVisualMapFlattenedState(bool isFlattened);
                
                VisualMapState GetCurrentVisualMapState() const;
            
                void StoreCurrentMapState();
                void RestorePreviousMapState();
                
            private:
                std::shared_ptr<IVisualMapModel> m_visualMapModel;
                std::shared_ptr<IVisualMapStateHistory> m_visualMapStateHistory;
            };
        }
    }
}