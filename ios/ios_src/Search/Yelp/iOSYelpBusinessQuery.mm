// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSYelpBusinessQuery.h"
#import <Foundation/Foundation.h>
#import "NSURLRequest+OAuth.h"
#include "YelpSearchJsonParser.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            static NSString * const APIHost           = @"api.yelp.com";
            static NSString * const BusinessPath      = @"/v2/business/";
            
            iOSYelpBusinessQuery::iOSYelpBusinessQuery(const std::string& yelpConsumerKey,
                                                       const std::string& yelpConsumerSecret,
                                                       const std::string& yelpOAuthToken,
                                                       const std::string& yelpOAuthTokenSecret,
                                                       SdkModel::IYelpCategoryMapper& yelpCategoryMapper,
                                                       const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                       Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
            : m_yelpConsumerKey(yelpConsumerKey)
            , m_yelpConsumerSecret(yelpConsumerSecret)
            , m_yelpOAuthToken(yelpOAuthToken)
            , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
            , m_yelpCategoryMapper(yelpCategoryMapper)
            , m_outdatedSearchResult(outdatedSearchResult)
            , m_callback(callback)
            , m_responseString()
            , m_cancelled(false)
            , m_isSuccess(false)
            , m_pTask(NULL)
            {
            }
            
            iOSYelpBusinessQuery::~iOSYelpBusinessQuery()
            {
                
            }
            
            void iOSYelpBusinessQuery::Dispatch()
            {
                NSString *businessPath = [NSString stringWithFormat:@"%@%@", BusinessPath, [NSString stringWithUTF8String:m_outdatedSearchResult.GetIdentifier().c_str()]];
                
                NSURLRequest *searchRequest = [NSURLRequest requestWithHost:APIHost
                                                                       path:businessPath
                                                                     params:@{ }
                                                                consumerKey:[NSString stringWithFormat:@"%s", m_yelpConsumerKey.c_str()]
                                                             consumerSecret:[NSString stringWithFormat:@"%s", m_yelpConsumerSecret.c_str()]
                                                                   tokenKey:[NSString stringWithFormat:@"%s", m_yelpOAuthToken.c_str()]
                                                                tokenSecret:[NSString stringWithFormat:@"%s", m_yelpOAuthTokenSecret.c_str()]];
                
                NSURLSession *session = [NSURLSession sharedSession];
                
                m_pTask = [session dataTaskWithRequest:searchRequest completionHandler:^(NSData *data,
                                                                                         NSURLResponse *response,
                                                                                         NSError *error)
                           {
                               NSHTTPURLResponse *httpResponse = static_cast<NSHTTPURLResponse*>(response);
                               m_isSuccess = (!error && httpResponse.statusCode == 200);
                               
                               if (m_isSuccess)
                               {
                                   const Byte* input = (Byte*)[data bytes];
                                   const size_t length = [data length];
                                   m_responseString = std::string(reinterpret_cast<char const*>(&(input[0])), length);
                               }
                               
                               dispatch_async(dispatch_get_main_queue(),
                                              ^{
                                                  DispatchCallback();
                                                  Eegeo_DELETE this;
                                              });
                           }];
                
                [m_pTask resume];
            }
            
            void iOSYelpBusinessQuery::Cancel()
            {
                Eegeo_ASSERT(m_pTask != NULL, "Cannot cancel iOSYelpBusinessQuery until query has been dispatched.\n");
                m_cancelled = true;
                [m_pTask cancel];
            }
            
            bool iOSYelpBusinessQuery::IsSucceeded()
            {
                return m_isSuccess;
            }
            
            const std::string& iOSYelpBusinessQuery::ResponseString()
            {
                return m_responseString;
            }
            
            void iOSYelpBusinessQuery::DispatchCallback()
            {
                if(!m_cancelled)
                {
                    ExampleApp::Search::SdkModel::SearchResultModel result;
                    if(TryParseYelpBusinessSearchResult(m_responseString, m_yelpCategoryMapper, result))
                    {
                        m_callback(ExampleApp::Search::SdkModel::IdentitySearchCallbackData::CreateSucceeded(result));
                    }
                    else
                    {
                        m_callback(ExampleApp::Search::SdkModel::IdentitySearchCallbackData::CreateFailed(m_outdatedSearchResult));
                    }
                }
                else
                {
                    m_callback(ExampleApp::Search::SdkModel::IdentitySearchCallbackData::CreateFailed(m_outdatedSearchResult));
                }
            }
        }
    }
}
