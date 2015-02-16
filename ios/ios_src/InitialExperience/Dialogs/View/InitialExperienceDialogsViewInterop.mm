// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsViewInterop.h"
#include "InitialExperienceDialogsView.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace Dialogs
        {
            namespace View
            {
                InitialExperienceDialogsViewInterop::InitialExperienceDialogsViewInterop(InitialExperienceDialogsView* pView)
                : m_pView(pView)
                {
                    
                }
                
                void InitialExperienceDialogsViewInterop::Open(const InitialExperienceDialogType::Values &dialogType,
                                                               const std::string &title,
                                                               const std::string &description)
                {
                    [m_pView showDialog:dialogType :&title :&description];
                }
                
                void InitialExperienceDialogsViewInterop::Close()
                {
                    [m_pView closeCurrentDialog];
                }
                
                void InitialExperienceDialogsViewInterop::SetModalBackground(bool active)
                {
                    [m_pView setModalBackgroundActive:active];
                }
                
                void InitialExperienceDialogsViewInterop::CloseButtonTapped()
                {
                    m_closedButtonTappedCallbacks.ExecuteCallbacks();
                }
                
                void InitialExperienceDialogsViewInterop::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_closedButtonTappedCallbacks.AddCallback(callback);
                }
                
                void InitialExperienceDialogsViewInterop::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_closedButtonTappedCallbacks.RemoveCallback(callback);
                }
            }
        }
    }
}