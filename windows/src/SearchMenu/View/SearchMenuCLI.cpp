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
}
