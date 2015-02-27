// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPinBoundObject.h"
#include "ICategorySearchRepository.h"
#include "MyPinsFileIO.h"
#include "SearchResultMyPinDetailsModelSelectedMessage.h"
#include "IWebLoadRequest.h"
#include "SearchResultPinAddedEvent.h"
#include "SearchResultPinRemovedEvent.h"
#include "TimeHelpers.h"
#include "IMyPinsSearchResultRefreshService.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            SearchResultPinBoundObject* SearchResultPinBoundObject::FromSerializedData(MyPinModel::TPinIdType pinId,
                                                                                       const std::string& serializedData,
                                                                                       MyPinsFileIO& myPinsFileIO,
                                                                                       CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                                                                       Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                                                       Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
            {
                return Eegeo_NEW(SearchResultPinBoundObject)(pinId,
                                                             Search::SdkModel::DeserializeFromJson(serializedData),
                                                             myPinsFileIO,
                                                             categorySearchRepository,
                                                             myPinsSearchResultRefreshService,
                                                             messageBus,
                                                             sdkModelDomainEventBus,
                                                             webLoadRequestFactory);
            }
            
            SearchResultPinBoundObject::SearchResultPinBoundObject(MyPinModel::TPinIdType pinId,
                                                                   const Search::SdkModel::SearchResultModel& searchResult,
                                                                   MyPinsFileIO& myPinsFileIO,
                                                                   CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                                                   Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                                   ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                                   Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
            : m_pinId(pinId)
            , m_searchResult(searchResult)
            , m_serialized(Search::SdkModel::SerializeToJson(m_searchResult))
            , m_myPinsFileIO(myPinsFileIO)
            , m_categorySearchRepository(categorySearchRepository)
            , m_myPinsSearchResultRefreshService(myPinsSearchResultRefreshService)
            , m_messageBus(messageBus)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_webLoadRequestFactory(webLoadRequestFactory)
            , m_webRequestCompleteCallback(this, &SearchResultPinBoundObject::WebRequestCompleteCallback)
            , m_pinVendorRequiresRefreshing(m_searchResult.GetVendor() == "Yelp")
            , m_isCurrentlyRefreshingResult(false)
            {
                
            }
            
            SearchResultPinBoundObject::~SearchResultPinBoundObject()
            {
                
            }
            
            void SearchResultPinBoundObject::HandlePinCreated(const MyPinModel& pinModel)
            {
                m_myPinsFileIO.SavePinModelToDisk(pinModel);
                SubmitPinToWebService(pinModel);
            }
            
            void SearchResultPinBoundObject::HandlePinAdded(const MyPinModel& pinModel)
            {
                m_sdkModelDomainEventBus.Publish(SearchResultPinAddedEvent(pinModel, m_searchResult));
            }
            
            void SearchResultPinBoundObject::HandlePinRemoved(const MyPinModel& pinModel)
            {
                m_sdkModelDomainEventBus.Publish(SearchResultPinRemovedEvent(pinModel, m_searchResult));
            }
            
            void SearchResultPinBoundObject::HandlePinDestroyed(const MyPinModel& pinModel)
            {
                // Nothing to do.
            }
            
            void SearchResultPinBoundObject::HandlePinSelected(const MyPinModel& pinModel)
            {
                m_messageBus.Publish(MyPinDetails::SearchResultMyPinDetailsModelSelectedMessage(m_searchResult));
            }
            
            void SearchResultPinBoundObject::HandlePinBecameFullyVisible(const MyPinModel& pinModel)
            {
                if(m_pinVendorRequiresRefreshing && !m_isCurrentlyRefreshingResult)
                {
                    const int64_t timeNow(Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                    const int64_t millisecondsSinceCreated(timeNow - m_searchResult.GetCreationTimestamp());
                    
                    // Allow at least five minutes between refreshes.
                    const int64_t millisecondsBetweenRefresh = (5 * 60 * 1000);

                    if(millisecondsSinceCreated >= millisecondsBetweenRefresh)
                    {
                        m_isCurrentlyRefreshingResult = true;
                        m_myPinsSearchResultRefreshService.RefreshPinnedSearchResult(pinModel.Identifier(),
                                                                                     *this,
                                                                                     m_searchResult);
                    }
                }
            }
            
            void SearchResultPinBoundObject::HandlePinBecameFullyInvisible(const MyPinModel& pinModel)
            {
                // Nothing to do.
            }
            
            MyPinsSemanticPinType SearchResultPinBoundObject::GetSemanticPinType() const
            {
                return SearchResultPoi;
            }
            
            std::string SearchResultPinBoundObject::GetIconForPin() const
            {
                const std::string& category(m_searchResult.GetCategory());
                
                std::string icon;
                if(!m_categorySearchRepository.TryGetCategorySearchIconByCategory(category, icon))
                {
                    icon = "misc";
                }
                
                return icon;
            }
            
            const std::string& SearchResultPinBoundObject::GetSerialized() const
            {
                return m_serialized;
            }
            
            void SearchResultPinBoundObject::SubmitPinToWebService(const MyPinModel& pinModel)
            {
                Eegeo_TTY("Here is where you submit pin to web service\n");
            }
            
            void SearchResultPinBoundObject::WebRequestCompleteCallback(Eegeo::Web::IWebLoadRequest& webLoadRequest)
            {
                Eegeo_TTY("Web Request Completed, code: %d\n", webLoadRequest.HttpStatusCode());
            }
            
            void SearchResultPinBoundObject::FinishRefreshingSearchResult(bool success,
                                                                          const Search::SdkModel::SearchResultModel& result)
            {
                m_isCurrentlyRefreshingResult = false;
                
                if(success)
                {
                    m_searchResult = result;
                    m_serialized = Search::SdkModel::SerializeToJson(m_searchResult);
                }
            }
        }
    }
}
