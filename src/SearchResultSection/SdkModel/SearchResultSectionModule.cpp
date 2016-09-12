// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionModule.h"

#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "SearchResultSection.h"
#include "SearchResultSectionOrder.h"
#include "SearchResultRepositoryObserver.h"
#include "SearchResultSectionItemSelectedMessageHandler.h"
#include "SearchResultViewClearedObserver.h"
#include "SearchResultSectionController.h"
#include "ISearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            void SearchResultSectionModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            {
                builder->registerType<View::SearchResultSectionMenuModel>().singleInstance();
                builder->registerType<View::SearchResultSectionOptionsModel>().singleInstance();
                builder->registerType<View::SearchResultRepositoryObserver>().singleInstance();
                builder->registerType<SearchResultSectionItemSelectedMessageHandler>().singleInstance();
                builder->registerType<SearchResultViewClearedObserver>().singleInstance();
                builder->registerType<View::SearchResultSectionOrder>().as<View::ISearchResultSectionOrder>().singleInstance();
                builder->registerType<View::SearchResultSectionController>().singleInstance();
            }
            
            void SearchResultSectionModule::RegisterLeaves()
            {
                RegisterLeaf<View::SearchResultRepositoryObserver>();
                RegisterLeaf<SearchResultSectionItemSelectedMessageHandler>();
                RegisterLeaf<SearchResultViewClearedObserver>();
                RegisterLeaf<View::SearchResultSectionController>();
            }
        }
    }
}
