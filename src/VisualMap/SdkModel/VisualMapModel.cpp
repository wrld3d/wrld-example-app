// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VisualMapModel.h"

namespace ExampleApp
{
    namespace VisualMap
    {
        namespace SdkModel
        {
            VisualMapModel::VisualMapModel(const VisualMapState& initialState)
            : m_currentState(initialState)
            {
                
            }
            
            void VisualMapModel::SetVisualMapState(const VisualMapState& visualMapState, bool storePreviousState)
            {
                VisualMapState oldState = m_currentState;
                m_currentState = visualMapState;
                m_visualMapStateChangedCallbacks.ExecuteCallbacks(oldState, storePreviousState);
            }

            VisualMapState VisualMapModel::GetVisualMapState() const
            {
                return m_currentState;
            }
            
            std::string VisualMapModel::GetTheme() const
            {
                return m_currentState.GetTheme();
            }
            
            std::string VisualMapModel::GetState() const
            {
                return m_currentState.GetState();
            }
            
            bool VisualMapModel::IsFlattened() const
            {
                return m_currentState.IsFlattened();
            }
            
            void VisualMapModel::AddVisualMapStateChangedCallback(Eegeo::Helpers::ICallback2<const VisualMapState&, const bool&>& callback)
            {
                m_visualMapStateChangedCallbacks.AddCallback(callback);
            }
            
            void VisualMapModel::RemoveVisualMapStateChangedCallback(Eegeo::Helpers::ICallback2<const VisualMapState&, const bool&>& callback)
            {
                m_visualMapStateChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}