// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SecondaryMenuCLI.h"
#include "Types.h"
#include "SecondaryMenuView.h"

#include <msclr\marshal_cppstd.h>

namespace ExampleApp
{
    void SecondaryMenuViewCLIMethods::PerformSearchQuery(System::IntPtr nativeCallerPointer, System::String^ searchTerm)
	{
		SecondaryMenu::View::SecondaryMenuView *view = (SecondaryMenu::View::SecondaryMenuView*)nativeCallerPointer.ToPointer();
        view->OnSearch(msclr::interop::marshal_as<std::string>(searchTerm));
	}
}
