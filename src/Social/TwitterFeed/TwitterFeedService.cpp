// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <map>
#include <sstream>
#include "document.h"
#include "TwitterFeedService.h"
#include "TweetRepository.h"
#include "TweetModel.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "WebLoadRequestCompletionCallback.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            const std::string TwitterFeedService::TwitterAuthUrl = "https://api.twitter.com/oauth2/token";
            const std::string TwitterFeedService::TwitterTimelineUrl = "https://api.twitter.com/1.1/statuses/user_timeline.json";
            
            const std::string TwitterFeedService::GrantTypeKey = "grant_type";
            const std::string TwitterFeedService::GrantTypeValue = "client_credentials";
            const std::string TwitterFeedService::TwitterAuthKey = "Authorization";
            const std::string TwitterFeedService::TwitterAuthValue = "Basic ";
            const std::string TwitterFeedService::ContentTypeKey = "Content-Type";
            const std::string TwitterFeedService::ContentTypeValue = "application/x-www-form-urlencoded;charset=UTF-8";
            const std::string TwitterFeedService::RequestAuthKey = "Authorization";
            const std::string TwitterFeedService::RequestAuthValue = "Bearer ";
            const std::string TwitterFeedService::AccessTokenKey = "access_token";
            
            const std::string TwitterFeedService::CountParameter = "count";
            const std::string TwitterFeedService::ScreenNameParameter = "screen_name";
            
            TwitterFeedService::TwitterFeedService(
                const std::string& twitterAuthCode, 
                Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
            : m_twitterAuthCode(twitterAuthCode)
            , m_accessToken("")
            , m_webLoadRequestFactory(webLoadRequestFactory)
            , m_pCurrentAuthRequest(NULL)
            , m_pCurrentTimeLineRequest(NULL)
            , m_pAuthCallback(Eegeo_NEW(Eegeo::Web::TWebLoadRequestCompletionCallback<TwitterFeedService>)(this, &TwitterFeedService::HandleAuthResponse))
            , m_pTimeLineCallback(Eegeo_NEW(Eegeo::Web::TWebLoadRequestCompletionCallback<TwitterFeedService>)(this, &TwitterFeedService::HandleTimeLineResponse))
            , m_currentServiceState(NOT_STARTED)
            {
                
            }
            
            TwitterFeedService::~TwitterFeedService()
            {
                if(m_pCurrentAuthRequest != NULL)
                {
                    m_pCurrentAuthRequest->Cancel();
                }
                
                if(m_pCurrentTimeLineRequest != NULL)
                {
                    m_pCurrentTimeLineRequest->Cancel();
                }
                
                Eegeo_DELETE m_pTimeLineCallback;
                Eegeo_DELETE m_pAuthCallback;
                
                for(std::map<std::string, TweetRepository*>::iterator it = m_repositoryMap.begin(); it != m_repositoryMap.end(); ++it)
                {
                    Eegeo_DELETE (*it).second;
                }
                
                m_repositoryMap.clear();
            }
            
            void TwitterFeedService::StartService()
            {
                m_pCurrentAuthRequest = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::POST, TwitterAuthUrl, *m_pAuthCallback)
                        .AddFormData(GrantTypeKey, GrantTypeValue)
                        .AddHeader(TwitterAuthKey, TwitterAuthValue + m_twitterAuthCode)
                        .AddHeader(ContentTypeKey, ContentTypeValue).Build();
                
                m_pCurrentAuthRequest->Load();
                
                m_currentServiceState = AUTHORIZING;
            }
            
            void TwitterFeedService::LoadNextTimeLine()
            {
                if(m_accountNameQueue.empty())
                {
                    m_currentServiceState = IDLE;
                    return;
                }
                
                std::stringstream timeLineURL;
                
                timeLineURL << TwitterTimelineUrl << "?" << CountParameter << "=" << MaxTweets << "&" << ScreenNameParameter << "=" << m_accountNameQueue.front();
                
                m_pCurrentTimeLineRequest = m_webLoadRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, timeLineURL.str(), *m_pTimeLineCallback)
                        .AddHeader(RequestAuthKey, RequestAuthValue + m_accessToken).Build();
                
                m_pCurrentTimeLineRequest->Load();
                
                m_currentServiceState = LOADING_TIMELINE;
            }
            
            void TwitterFeedService::LoadTimeline(const std::string& userId)
            {
                m_accountNameQueue.push(userId);
                
                switch (m_currentServiceState)
                {
                    case NOT_STARTED:
                        StartService();
                        break;
                    case AUTHORIZING:
                        break;
                    case LOADING_TIMELINE:
                        break;
                    case IDLE:
                        LoadNextTimeLine();
                        break;
                    case OFFLINE:
                        ClearAccountNameQueue();
                        break;
                    default:
                        Eegeo_ASSERT(false, "Unhandled service state for TwitterFeedService");
                        break;
                }
            }
            
            void TwitterFeedService::LoadTimeLines(const std::vector<std::string>& userIds)
            {
                for(std::vector<std::string>::const_iterator it = userIds.begin(); it != userIds.end(); ++it)
                {
                    LoadTimeline(*it);
                }
            }
            
            bool TwitterFeedService::ContainsTweetRepositoryForUserId(std::string userId) const
            {
                return m_repositoryMap.find(userId) != m_repositoryMap.end();
            }
            
            const TweetRepository& TwitterFeedService::GetTweetRepositoryForUserId(std::string userId) const
            {
                std::map<std::string, TweetRepository*>::const_iterator repositoryIt = m_repositoryMap.find(userId);
                
                Eegeo_ASSERT(repositoryIt != m_repositoryMap.end());
                
                return *((*repositoryIt).second);
            }
            
            void TwitterFeedService::HandleAuthResponse(Eegeo::Web::IWebResponse& webResponse)
            {
                m_pCurrentAuthRequest = NULL;
                
                if(webResponse.GetHttpStatusCode() != 200)
                {
                    m_currentServiceState = OFFLINE;
                    
                    ClearAccountNameQueue();
                    
                    return;
                }
                
                size_t resultSize = webResponse.GetBodyData().size();
                std::string serialized(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);
                
                rapidjson::Document document;
                
                document.Parse<0>(serialized.c_str());
                
                Eegeo_ASSERT(!document.HasParseError(), "Error parsing auth response");
                Eegeo_ASSERT(document.HasMember(AccessTokenKey.c_str()), "Auth response doesn't contain access code: %s", serialized.c_str());
                
                m_accessToken = std::string(document[AccessTokenKey.c_str()].GetString());
                
                LoadNextTimeLine();
            }
            
            void TwitterFeedService::HandleTimeLineResponse(Eegeo::Web::IWebResponse& webResponse)
            {
                m_pCurrentTimeLineRequest = NULL;
                
                if(webResponse.GetHttpStatusCode() != 200)
                {
                    m_currentServiceState = OFFLINE;
                    
                    ClearAccountNameQueue();
                    
                    return;
                }
                
                size_t resultSize = webResponse.GetBodyData().size();
                std::string serialized(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);
                
                rapidjson::Document document;
                
                document.Parse<0>(serialized.c_str());
                
                Eegeo_ASSERT(!document.HasParseError(), "Error parsing timeline request response")
                Eegeo_ASSERT(document.IsArray(), "Timeline request response unrecognised: %s", serialized.c_str());
                
                std::map<std::string, TweetRepository*>::iterator repositoryIt = m_repositoryMap.find(m_accountNameQueue.front());
                
                if(repositoryIt == m_repositoryMap.end())
                {
                    repositoryIt = m_repositoryMap.insert(std::pair<std::string, TweetRepository*>(m_accountNameQueue.front(), Eegeo_NEW(TweetRepository)())).first;
                }
                
                TweetRepository* currentRepository = (*repositoryIt).second;
                
                for(rapidjson::SizeType i = 0; i < document.Size(); ++i)
                {
                    currentRepository->AddItem(TweetModel::GetNewTweetModelFromJsonDocument(document, i));
                }
                
                m_feedLoadedCallbacks.ExecuteCallbacks(m_accountNameQueue.front(), *currentRepository);
                
                m_accountNameQueue.pop();
                
                LoadNextTimeLine();
            }
            
            void TwitterFeedService::ClearAccountNameQueue()
            {
                while (!m_accountNameQueue.empty())
                {
                    m_accountNameQueue.pop();
                }
            }
            
            void TwitterFeedService::AddFeedLoadedCallback(Eegeo::Helpers::ICallback2<const std::string&, TweetRepository&>& callback)
            {
                m_feedLoadedCallbacks.AddCallback(callback);
            }
            
            void TwitterFeedService::RemoveFeedLoadedCallback(Eegeo::Helpers::ICallback2<const std::string&, TweetRepository&>& callback)
            {
                m_feedLoadedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
