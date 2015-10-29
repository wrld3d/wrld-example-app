// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorExplorerUserInteractionModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorExplorerUserInteractionModel::InteriorExplorerUserInteractionModel()
            : m_enabled(true)
            {
            }
            
            void InteriorExplorerUserInteractionModel::SetEnabled(bool enabled)
            {
                if(m_enabled != enabled)
                {
                    m_enabled = enabled;
                    m_enabledChangedCallbacks.ExecuteCallbacks();
                }
            }
            
            bool InteriorExplorerUserInteractionModel::IsEnabled() const
            {
                return m_enabled;
            }
            
            void InteriorExplorerUserInteractionModel::InsertEnabledChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_enabledChangedCallbacks.AddCallback(callback);
            }
            
            void InteriorExplorerUserInteractionModel::RemoveEnabledChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_enabledChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
