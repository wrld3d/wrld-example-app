// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
			void SearchResultPoiViewModule::Register(const TContainerBuilder& builder)
			{
				ASSERT_UI_THREAD
				builder->registerType<SearchResultPoiView>().as<ISearchResultPoiView>().singleInstance();
			}

			void SearchResultPoiViewModule::RegisterLeaves()
			{
				RegisterLeaf<SearchResultPoiView>();
			}
        }
    }
}
