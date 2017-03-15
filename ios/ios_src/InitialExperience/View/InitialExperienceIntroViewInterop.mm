// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroViewInterop.h"
#include "InitialExperienceIntroView.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            InitialExperienceIntroViewInterop::InitialExperienceIntroViewInterop(InitialExperienceIntroView* pView, InitialExperienceIntroBackgroundView* pBackgroundView)
            : m_pView(pView)
            , m_pBackgroundView(pBackgroundView)
            {
                
            }
            
            void InitialExperienceIntroViewInterop::Show()
            {
                [m_pView show];
                [m_pBackgroundView show];
            }
            
            void InitialExperienceIntroViewInterop::Dismiss()
            {
                [m_pView dismiss];
                [m_pBackgroundView dismiss];
            }
            
            void InitialExperienceIntroViewInterop::OnDismiss()
            {
                Dismiss();
                m_dismissedCallbacks.ExecuteCallbacks();
            }
            
            void InitialExperienceIntroViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissedCallbacks.AddCallback(callback);
            }
            
            void InitialExperienceIntroViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                m_dismissedCallbacks.RemoveCallback(callback);
            }
            
            void InitialExperienceIntroViewInterop::ShowExitIUX()
            {
            }
            
            void InitialExperienceIntroViewInterop::DismissExitIUX()
            {
            }
        }
    }
}
