// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPinBoundObject.h"
#include "ITagSearchRepository.h"
#include "MyPinsFileIO.h"
#include "SearchResultMyPinDetailsModelSelectedMessage.h"
#include "IWebLoadRequest.h"
#include "SearchResultPinAddedEvent.h"
#include "SearchResultPinRemovedEvent.h"
#include "TimeHelpers.h"
#include "IMyPinsSearchResultRefreshService.h"
#include "IMyPinsService.h"
#include "SearchResultIconKeyMapper.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            SearchResultPinBoundObject* SearchResultPinBoundObject::FromSerializedData(MyPinModel::TPinIdType pinId,
                                                                                       const std::string& pinMetadataJson,
                                                                                       const std::string& pinIconKey,
                                                                                       MyPinsFileIO& myPinsFileIO,
                                                                                       Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                                                       ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                                                       ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService)
            {
                Eegeo_ASSERT(!pinIconKey.empty());

                Search::SdkModel::SearchResultModel searchResultModel;
                
                if(!Search::SdkModel::TryDeserializeFromJson(pinMetadataJson, searchResultModel))
                {
                    return NULL;
                }

                return Eegeo_NEW(SearchResultPinBoundObject)(pinId,
                                                             searchResultModel,
                                                             pinIconKey,
                                                             myPinsFileIO,
                                                             myPinsSearchResultRefreshService,
                                                             messageBus,
                                                             sdkModelDomainEventBus,
                                                             myPinsService);
            }
            
            SearchResultPinBoundObject::SearchResultPinBoundObject(MyPinModel::TPinIdType pinId,
                                                                   const Search::SdkModel::SearchResultModel& searchResult,
                                                                   const std::string& pinIconKey,
                                                                   MyPinsFileIO& myPinsFileIO,
                                                                   Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                                   ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                                                   ExampleApp::MyPins::SdkModel::IMyPinsService& myPinsService)
            : m_searchResult(searchResult)
            , m_pinIconKey(pinIconKey)
            , m_myPinsFileIO(myPinsFileIO)
            , m_myPinsSearchResultRefreshService(myPinsSearchResultRefreshService)
            , m_messageBus(messageBus)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_pinVendorRequiresRefreshing(m_searchResult.GetVendor() == Search::YelpVendorName)
            , m_isCurrentlyRefreshingResult(false)
            , m_myPinsService(myPinsService)
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

                    if(millisecondsSinceCreated >= millisecondsBetweenRefresh || pinModel.Version() != MyPinModel::CurrentVersion)
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
                return m_pinIconKey;
            }
            
            std::string SearchResultPinBoundObject::GetSerialized() const
            {
                return Search::SdkModel::SerializeToJson(m_searchResult);
            }
            
            void SearchResultPinBoundObject::SubmitPinToWebService(const MyPinModel& pinModel)
            {
                Eegeo_TTY("Here is where you submit pin to web service\n");
            }
            
            void SearchResultPinBoundObject::FinishRefreshingSearchResult(bool success,
                                                                          const ExampleApp::MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                                          const Search::SdkModel::SearchResultModel& result)
            {
                m_isCurrentlyRefreshingResult = false;
                
                if(success)
                {
                    m_searchResult = result;
                    
                    m_myPinsService.UpdatePinWithResult(pinId, result);
                }
            }
        }
    }
}
