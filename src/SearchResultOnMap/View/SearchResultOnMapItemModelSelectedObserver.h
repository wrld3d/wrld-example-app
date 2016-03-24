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
                SearchResultPoi::View::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultOnMapItemModelSelectedObserver, const SearchResultOnMapItemModelSelectedMessage&> m_handlerBinding;

                void OnSearchResultOnMapItemModelSelectedMessage(const SearchResultOnMapItemModelSelectedMessage& message);

                const Menu::View::IMenuReactionModel& m_menuReaction;

            public:
                SearchResultOnMapItemModelSelectedObserver(SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                        ExampleAppMessaging::TMessageBus& messageBus,
                        const Menu::View::IMenuReactionModel& menuReaction);

                ~SearchResultOnMapItemModelSelectedObserver();
            };
        }
    }
}
