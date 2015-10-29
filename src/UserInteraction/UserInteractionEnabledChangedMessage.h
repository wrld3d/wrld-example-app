// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace UserInteraction
    {
        class UserInteractionEnabledChangedMessage
        {
        private:
            bool m_enabled;
        
        public:
            UserInteractionEnabledChangedMessage(bool enabled)
            : m_enabled(enabled)
            {
            }
            
            bool IsEnabled() const
            {
                return m_enabled;
            }
        };
    }
}
