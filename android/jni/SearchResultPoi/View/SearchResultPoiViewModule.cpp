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
				builder->registerType<SearchResultPoiView>().as<ISearchResultPoiView>().singleInstance();
			}

			void SearchResultPoiViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("SearchResultPoiViewModule::RegisterUiLeaves begin");
				RegisterLeaf<SearchResultPoiView>();
				Eegeo_TTY("SearchResultPoiViewModule::RegisterUiLeaves end");
			}
        }
    }
}
