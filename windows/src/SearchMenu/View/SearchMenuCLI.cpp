// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuCLI.h"
#include "SearchMenuView.h"

#include <msclr\marshal_cppstd.h>

namespace ExampleApp
{
    void SearchMenuViewCLIMethods::PerformedSearchQuery(System::IntPtr nativeCallerPointer, System::String^ text)
    {
        SearchMenu::View::SearchMenuView *view = (SearchMenu::View::SearchMenuView *)nativeCallerPointer.ToPointer();
        view->SearchPerformed(msclr::interop::marshal_as<std::string>(text));
    }

    void SearchMenuViewCLIMethods::OnSearchCleared(System::IntPtr nativeCallerPointer)
    {
        SearchMenu::View::SearchMenuView *view = (SearchMenu::View::SearchMenuView *)nativeCallerPointer.ToPointer();
        view->OnSearchCleared();
    }

    void SearchMenuViewCLIMethods::HandleSearchItemSelected(System::IntPtr nativeCallerPointer, int itemIndex)
    {
        SearchMenu::View::SearchMenuView *view = (SearchMenu::View::SearchMenuView *)nativeCallerPointer.ToPointer();
        view->HandleSearchItemSelected(itemIndex);
    }
}
