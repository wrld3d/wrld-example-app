// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionModel.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionModel::UserInteractionModel()
            : m_enabled(true)
            {
            }
            
            void UserInteractionModel::SetEnabled(bool enabled)
            {
                if(m_enabled != enabled)
                {
                    m_enabled = enabled;
                    m_enabledChangedCallbacks.ExecuteCallbacks();
                }
            }
            
            bool UserInteractionModel::IsEnabled() const
            {
                return m_enabled;
            }
            
            void UserInteractionModel::InsertEnabledChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_enabledChangedCallbacks.AddCallback(callback);
            }
            
            void UserInteractionModel::RemoveEnabledChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_enabledChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
