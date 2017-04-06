// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageCLI.h"
#include "AboutPageView.h"

namespace ExampleApp
{
    void AboutPageCLI::CloseButtonClicked(System::IntPtr^ nativeObjectPtr)
    {
        AboutPage::View::AboutPageView* view = reinterpret_cast<AboutPage::View::AboutPageView*>(nativeObjectPtr->ToPointer());
        view->CloseTapped();
    }

    void AboutPageCLI::LogoLongPress(System::IntPtr^ nativeObjectPtr)
    {
        AboutPage::View::AboutPageView* view = reinterpret_cast<AboutPage::View::AboutPageView*>(nativeObjectPtr->ToPointer());
        view->ShowHiddenText();
    }
}