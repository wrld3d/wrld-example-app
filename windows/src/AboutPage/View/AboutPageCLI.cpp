// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageCLI.h"
#include "AboutPageView.h"

namespace ExampleApp
{
    void AboutPageCLI::CloseButtonClicked(System::IntPtr^ nativeObejctPtr)
    {
        AboutPage::View::AboutPageView* view = reinterpret_cast<AboutPage::View::AboutPageView*>(nativeObejctPtr->ToPointer());
        view->CloseTapped();
    }
}