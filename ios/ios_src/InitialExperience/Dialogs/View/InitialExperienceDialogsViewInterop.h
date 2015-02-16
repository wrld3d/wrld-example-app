// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInitialExperienceDialogsView.h"
#include "InitialExperienceDialogType.h"
#include "InitialExperienceDialogsViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include <string>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace Dialogs
        {
            namespace View
            {
                class InitialExperienceDialogsViewInterop : public IInitialExperienceDialogsView, private Eegeo::NonCopyable
                {
                public:
                    InitialExperienceDialogsViewInterop(InitialExperienceDialogsView* pView);
                    
                    void Open(const InitialExperienceDialogType::Values& dialogType, const std::string& title, const std::string &description);
                    void Close();
                    void SetModalBackground(bool active);
                    
                    void CloseButtonTapped();
                    
                    void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
                    
                private:
                    
                    InitialExperienceDialogsView* m_pView;
                    Eegeo::Helpers::CallbackCollection0 m_closedButtonTappedCallbacks;

                };
            }
        }
    }
}