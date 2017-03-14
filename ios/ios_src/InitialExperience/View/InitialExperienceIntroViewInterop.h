// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "InitialExperienceIntroViewIncludes.h"
#include "IInitialExperienceIntroView.h"
#include <string>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroViewInterop : public IInitialExperienceIntroView, private Eegeo::NonCopyable
            {
            public:
                InitialExperienceIntroViewInterop(InitialExperienceIntroView* pView, InitialExperienceIntroBackgroundView* pBackgroundView);
                
                void Show();
                void Dismiss();
                
                void OnDismiss();
                
                void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void ShowExitIUX();
                void DismissExitIUX();
                
            private:
                
                InitialExperienceIntroView* m_pView;
                InitialExperienceIntroBackgroundView* m_pBackgroundView;
                
                Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                
            };
        }
    }
}
