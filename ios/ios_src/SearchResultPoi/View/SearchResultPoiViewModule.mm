// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiController.h"
#include "SearchResultPoiViewContainer.h"
#include "SearchResultPoiViewInterop.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            void SearchResultPoiViewModule::Register(const TContainerBuilder &builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = [[SearchResultPoiViewContainer alloc] initWithoutParams];
                                                     return std::make_shared<SearchResultPoiViewContainerWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<SearchResultPoiViewContainerWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getInterop]);
                                                 }).as<ISearchResultPoiView>().singleInstance();
            }
        }
    }
}
