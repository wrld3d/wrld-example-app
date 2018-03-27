// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

namespace Eegeo
{
    namespace iOS
    {
        class iOSLocationService;
    }
}

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewInterop;
        }
    }
    namespace NavUI
    {
        namespace View
        {
            class NavUIViewModule: private Eegeo::NonCopyable
            {
            public:
                NavUIViewModule(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop,
                                Eegeo::iOS::iOSLocationService* iOSLocationService);

                ~NavUIViewModule();

                UIView& GetNavUIView() const;
                
            private:
                struct Private;
                Private* d;
            };
        }
    }
}
