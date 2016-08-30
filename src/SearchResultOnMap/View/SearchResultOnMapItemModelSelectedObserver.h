// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "ISearchResultPoiViewModel.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            class SearchResultOnMapItemModelSelectedObserver : private Eegeo::NonCopyable
            {
                const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel> m_searchResultPoiViewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultOnMapItemModelSelectedObserver, const SearchResultOnMapItemModelSelectedMessage&> m_handlerBinding;

                void OnSearchResultOnMapItemModelSelectedMessage(const SearchResultOnMapItemModelSelectedMessage& message);

                const std::shared_ptr<const Menu::View::IMenuReactionModel> m_menuReaction;

            public:
                SearchResultOnMapItemModelSelectedObserver(const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel>& searchResultPoiViewModel,
                                                           const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                           const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction);

                ~SearchResultOnMapItemModelSelectedObserver();
            };
        }
    }
}
