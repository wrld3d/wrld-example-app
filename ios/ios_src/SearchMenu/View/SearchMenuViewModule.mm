// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuViewModule.h"

#include "MenuViewInterop.h"
#include "ScreenProperties.h"
#include "SearchMenuView.h"
#include "SearchMenuViewInterop.h"
#include "SearchMenuOptions.h"
#include "SearchMenuController.h"
#include "CustomTableDataProvider.h"
#include "SearchResultsTableDataProvider.h"
#include "ITagSearchRepository.h"
#include "IModalBackgroundView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            void SearchMenuViewModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = [CustomTableDataProvider alloc];
                                                     return std::make_shared<CustomTableDataProviderWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = [SearchResultsTableDataProvider alloc];
                                                     return std::make_shared<SearchResultsTableDataProviderWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                                     auto dataProvider = context.resolve<CustomTableDataProviderWrapper>()->Get();
                                                     auto searchDataProvider = context.resolve<SearchResultsTableDataProviderWrapper>()->Get();
                                                     auto searchMenuViewModel = context.resolve<View::SearchMenuViewModel>();
                                                     auto view = [[SearchMenuView alloc] initWithParams:screenProperties->GetScreenWidth()
                                                                                                       :screenProperties->GetScreenHeight()
                                                                                                       :screenProperties->GetPixelScale()
                                                                                                       :dataProvider
                                                                                                       :static_cast<int>(searchMenuViewModel->SectionsCount())
                                                                                                       :searchDataProvider];
                                                     return std::make_shared<SearchMenuViewWrapper>(view);
                                                 }).singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<SearchMenuViewWrapper>();
                                                     return Hypodermic::makeExternallyOwned(*[view->Get() getSearchMenuInterop]);
                                                 }).as<ISearchMenuView>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                 {
                                                     auto view = context.resolve<SearchMenuViewWrapper>();
                                                     auto menuInterop = [view->Get() getInterop];
                                                     return std::make_shared<SearchMenuController>(
                                                                                                   context.resolve<SearchMenuModel>(),
                                                                                                   context.resolve<SearchMenuViewModel>(),
                                                                                                   Hypodermic::makeExternallyOwned(*menuInterop),
                                                                                                   context.resolve<ISearchMenuView>(),
                                                                                                   context.resolve<SearchMenuSectionViewModel>(),
                                                                                                   context.resolve<TagSearch::View::ITagSearchRepository>(),
                                                                                                   context.resolve<Modality::View::IModalBackgroundView>(),
                                                                                                   context.resolve<ExampleAppMessaging::TMessageBus>());
                                                 }).singleInstance();
            }
        }
    }
}
