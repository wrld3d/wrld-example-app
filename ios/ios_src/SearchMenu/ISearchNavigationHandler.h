// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <WrldSearchWidget/WrldSearchWidget.h>

namespace ExampleApp
{
    namespace SearchMenu
    {
        class ISearchNavigationHandler
        {
        public:
            virtual void NavigateTo(id<WRLDSearchResultModel> resultModel) = 0;
        };
    }
}
