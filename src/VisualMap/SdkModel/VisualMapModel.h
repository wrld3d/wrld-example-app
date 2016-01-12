// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IVisualMapModel.h"
#include "VisualMapState.h"
#include "CallbackCollection.h"

#include "Types.h"

#include <string>

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            class VisualMapModel : public IVisualMapModel, protected Eegeo::NonCopyable
            {
            public:
                explicit VisualMapModel(const VisualMapState& initialState);
                
                void SetVisualMapState(const VisualMapState& visualMapState, bool storePreviousState);
                
                VisualMapState GetVisualMapState() const;
                std::string GetTheme() const;
                std::string GetState() const;
                bool IsFlattened() const;
                
                void AddVisualMapStateChangedCallback(Eegeo::Helpers::ICallback2<const VisualMapState&, const bool&>& callback);
                void RemoveVisualMapStateChangedCallback(Eegeo::Helpers::ICallback2<const VisualMapState&, const bool&>& callback);
            private:
                VisualMapState m_currentState;
                
                Eegeo::Helpers::CallbackCollection2<const VisualMapState&, const bool&> m_visualMapStateChangedCallbacks;
            };
        }
    }
}