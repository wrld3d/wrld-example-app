// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiViewModel.h"
#include "Logger.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "FlurryWrapper.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            SearchResultOnMapItemModel::SearchResultOnMapItemModel(Search::SdkModel::SearchResultModel& searchResultModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchResultModel(searchResultModel)
                , m_messageBus(messageBus)
            {

            }

            SearchResultOnMapItemModel::~SearchResultOnMapItemModel()
            {

            }

            void SearchResultOnMapItemModel::SelectPin()
            {
                FLURRY_SET_EVENT("Pin Selected", "Name", m_searchResultModel.GetTitle().c_str());
                m_messageBus.Publish(SearchResultOnMapItemModelSelectedMessage(m_searchResultModel));
            }
        }
    }
}
