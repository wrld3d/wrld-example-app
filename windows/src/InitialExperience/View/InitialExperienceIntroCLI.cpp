// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InitialExperienceIntroCLI.h"
#include "InitialExperienceIntroView.h"

namespace ExampleApp
{
    void InitialExperienceIntroCLIMethods::HandleClick(System::IntPtr nativeCallerPointer)
    {
        InitialExperience::View::InitialExperienceIntroView *view = (InitialExperience::View::InitialExperienceIntroView*)nativeCallerPointer.ToPointer();
        view->OnDismiss();
    }
}