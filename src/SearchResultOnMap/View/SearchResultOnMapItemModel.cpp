// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiViewModel.h"
#include "Logger.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            SearchResultOnMapItemModel::SearchResultOnMapItemModel(const Search::SdkModel::SearchResultModel& searchResultModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService)
                : m_searchResultModel(searchResultModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_availabilityChangedHandlerBinding(this, &SearchResultOnMapItemModel::OnAvailabilityChanged)
            {
                m_messageBus.SubscribeNative(m_availabilityChangedHandlerBinding);
            }

            SearchResultOnMapItemModel::~SearchResultOnMapItemModel()
            {
                m_messageBus.UnsubscribeNative(m_availabilityChangedHandlerBinding);
            }

            void SearchResultOnMapItemModel::SelectPin()
            {
                m_metricsService.SetEvent("Pin Selected", "Name", m_searchResultModel.GetTitle().c_str());
                m_messageBus.Publish(SearchResultOnMapItemModelSelectedMessage(m_searchResultModel));
            }
            
            void SearchResultOnMapItemModel::OnAvailabilityChanged(const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged& message)
            {
                
                const Search::SdkModel::SearchResultModel& updatedModel = message.GetModel();
                
                if(m_searchResultModel.GetIdentifier() == updatedModel.GetIdentifier())
                {
                    int tempState = Search::Swallow::SearchConstants::GetAvailabilityStateFromAvailability(message.GetAvailability());
                    m_searchResultModel.SetAvailability(tempState);
                }
            }
        }
    }
}
