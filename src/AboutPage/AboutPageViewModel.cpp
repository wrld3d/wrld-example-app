// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewModel.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageViewModel::AboutPageViewModel(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel)
        : m_openable(identity, reactionControllerModel)
        {
            
        }
        
        AboutPageViewModel::~AboutPageViewModel()
        {
            
        }
        
        bool AboutPageViewModel::TryAcquireReactorControl()
        {
            return m_openable.TryAcquireReactorControl();
        }
        
        bool AboutPageViewModel::IsOpen() const
        {
            return m_openable.IsFullyOpen();
        }
        
        void AboutPageViewModel::Open()
        {
            if(!IsOpen())
        	{
            	if(m_openable.Open())
                {
                    m_openedCallbacks.ExecuteCallbacks();
                }
        	}
        }
        
        void AboutPageViewModel::Close()
        {
            if(IsOpen())
        	{
            	{
					const bool closed = m_openable.Close();
					Eegeo_ASSERT(closed, "Failed to close");
            	}

                m_closedCallbacks.ExecuteCallbacks();
        	}
        }
        
        OpenableControlViewModel::IOpenableControlViewModel& AboutPageViewModel::GetOpenableControl()
        {
            return m_openable;
        }
        
        void AboutPageViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
        {
            m_openedCallbacks.AddCallback(openedCallback);
        }
        
        void AboutPageViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
        {
            m_openedCallbacks.RemoveCallback(openedCallback);
        }
        
        void AboutPageViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
        {
            m_closedCallbacks.AddCallback(closedCallback);
        }
        
        void AboutPageViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
        {
            m_closedCallbacks.RemoveCallback(closedCallback);
        }
    }
}
