// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

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
                NavUIViewModule(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* searchResultsPoiViewInterop);

                ~NavUIViewModule();

                UIView& GetNavUIView() const;
                
            private:
                struct Private;
                Private* d;
            };
        }
    }
}
