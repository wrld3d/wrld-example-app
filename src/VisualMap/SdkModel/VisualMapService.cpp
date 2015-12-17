// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VisualMapService.h"
#include "IVisualMapModel.h"
#include "IVisualMapStateHistory.h"
#include "VisualMapState.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            VisualMapService::VisualMapService(IVisualMapModel& visualMapModel,
                                               IVisualMapStateHistory& visualMapStateHistory)
            : m_visualMapModel(visualMapModel)
            , m_visualMapStateHistory(visualMapStateHistory)
            {
                
            }
            
            void VisualMapService::SetVisualMapState(const VisualMapState& visualMapState)
            {
                const bool preservePreviousState = true;
                m_visualMapModel.SetVisualMapState(visualMapState, preservePreviousState);
            }
            
            void VisualMapService::SetVisualMapState(const std::string& theme, const std::string& state, bool isFlattened)
            {
                SetVisualMapState(VisualMapState(theme, state, isFlattened));
            }
            
            void VisualMapService::SetVisualMapTheme(const std::string& theme)
            {
                const VisualMapState& currentState = m_visualMapModel.GetVisualMapState();
                SetVisualMapState(theme, currentState.GetState(), currentState.IsFlattened());
            }
            
            void VisualMapService::SetVisualMapThemeState(const std::string& state)
            {
                const VisualMapState& currentState = m_visualMapModel.GetVisualMapState();
                SetVisualMapState(currentState.GetTheme(), state, currentState.IsFlattened());
            }
            
            void VisualMapService::SetVisualMapFlattenedState(bool isFlattened)
            {
                const VisualMapState& currentState = m_visualMapModel.GetVisualMapState();
                SetVisualMapState(currentState.GetTheme(), currentState.GetState(), isFlattened);
            }
            
            VisualMapState VisualMapService::GetCurrentVisualMapState() const
            {
                return m_visualMapModel.GetVisualMapState();
            }
            
            void VisualMapService::StoreCurrentMapState()
            {
                const VisualMapState& currentState = m_visualMapModel.GetVisualMapState();
                m_visualMapStateHistory.Push(currentState);
            }
            
            void VisualMapService::RestorePreviousMapState()
            {
                const VisualMapState& previousState = m_visualMapStateHistory.Pop();
                
                const bool preservePreviousState = false;
                m_visualMapModel.SetVisualMapState(previousState, preservePreviousState);
            }
        }
    }
}