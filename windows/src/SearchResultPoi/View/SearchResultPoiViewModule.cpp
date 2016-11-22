// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiController.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "DesktopSearchResultPoiController.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            void SearchResultPoiViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<SearchResultPoiView>().as<ISearchResultPoiView>().singleInstance();
                builder->registerType<DesktopSearchResultPoiController>().as<SearchResultPoiController>().singleInstance();
            }

            void SearchResultPoiViewModule::RegisterUiLeaves()
            {
                RegisterLeaf<SearchResultPoiController>();
            }
        }
    }
}
