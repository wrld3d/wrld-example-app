// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuCLI.h"
#include "SearchMenuView.h"
#include "WindowsAppThreadAssertionMacros.h"

void SearchMenuViewCLIMethods::HandleClosed(System::IntPtr nativeObjectPtr)
{
    ExampleApp::SearchResultMenu::View::SearchMenuView* pView = reinterpret_cast<ExampleApp::SearchResultMenu::View::SearchMenuView*>(nativeObjectPtr.ToPointer());
    pView->HandleSearchClosed();
}
