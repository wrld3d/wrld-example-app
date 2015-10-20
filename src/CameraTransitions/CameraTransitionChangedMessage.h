// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace CameraTransitions
    {
        class CameraTransitionChangedMessage
        {
        public:
            
            CameraTransitionChangedMessage(bool transitionInProgress)
            : m_transitionInProgress(transitionInProgress)
            {
                
            }
            
            const bool IsTransitionInProgress() const { return m_transitionInProgress; }
            
        private:
            const bool m_transitionInProgress;
        };
    }
}