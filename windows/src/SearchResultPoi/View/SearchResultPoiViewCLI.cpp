// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewCLI.h"
#include "SearchResultPoiView.h"
#include "ReflectionHelpers.h"

namespace ExampleApp
{
    void SearchResultPoiViewCLI::CloseButtonClicked(System::IntPtr nativeCallerPointer)
    {
        SearchResultPoi::View::SearchResultPoiView *view = (SearchResultPoi::View::SearchResultPoiView*)nativeCallerPointer.ToPointer();
        view->HandleCloseClicked();
    }

    void SearchResultPoiViewCLI::TogglePinnedButtonClicked(System::IntPtr nativeCallerPointer)
    {
        SearchResultPoi::View::SearchResultPoiView *view = (SearchResultPoi::View::SearchResultPoiView*)nativeCallerPointer.ToPointer();
        view->HandlePinToggleClicked();
    }

	void SearchResultPoiViewCLI::AvailabilityChanged(System::IntPtr nativeCallerPointer, System::String^ availability)
	{
		SearchResultPoi::View::SearchResultPoiView *view = (SearchResultPoi::View::SearchResultPoiView*)nativeCallerPointer.ToPointer();
		view->HandleAvailabilityChanged(Helpers::ReflectionHelpers::ConvertManagedStringToUTF8(availability));
	}
}