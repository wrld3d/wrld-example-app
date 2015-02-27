// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSYelpSearchQuery.h"
#import <Foundation/Foundation.h>
#import "NSURLRequest+OAuth.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            static NSString * const APIHost           = @"api.yelp.com";
            static NSString * const SearchPath        = @"/v2/search/";
            static NSString * const SearchLimit       = @"20";
            static float const MaxRadiusMetres        = 40000.f;
            
            iOSYelpSearchQuery::iOSYelpSearchQuery(const std::string& yelpConsumerKey,
                                                   const std::string& yelpConsumerSecret,
                                                   const std::string& yelpOAuthToken,
                                                   const std::string& yelpOAuthTokenSecret,
                                                   const SdkModel::SearchQuery& searchQuery,
                                                   Eegeo::Helpers::ICallback0& completionCallback)
            : m_yelpConsumerKey(yelpConsumerKey)
            , m_yelpConsumerSecret(yelpConsumerSecret)
            , m_yelpOAuthToken(yelpOAuthToken)
            , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
            , m_searchQuery(searchQuery)
            , m_completionCallback(completionCallback)
            , m_responseString()
            , m_cancelled(false)
            , m_isSuccess(false)
            , m_pTask(NULL)
            {
            }
            
            iOSYelpSearchQuery::~iOSYelpSearchQuery()
            {
                
            }
            
            void iOSYelpSearchQuery::Dispatch()
            {
                const double latDegrees(m_searchQuery.Location().GetLatitudeInDegrees());
                const double lonDegrees(m_searchQuery.Location().GetLongitudeInDegrees());
                NSString* searchLocationStr = [NSString stringWithFormat:@"%f,%f", latDegrees, lonDegrees];
                int radiusFilter = static_cast<int>(m_searchQuery.Radius() > MaxRadiusMetres || !m_searchQuery.IsCategory()
                                                    ? MaxRadiusMetres
                                                    : m_searchQuery.Radius());
                NSString* radiusFilterStr = [NSString stringWithFormat:@"%d", radiusFilter];
                NSString* categoryFilterStr = @"";
                NSString* searchQueryStr = @"";
                
                if(m_searchQuery.IsCategory())
                {
                    categoryFilterStr = [NSString stringWithUTF8String:m_searchQuery.Query().c_str()];
                }
                else
                {
                    searchQueryStr = [NSString stringWithUTF8String:m_searchQuery.Query().c_str()];
                }
                
                NSDictionary *params = @{
                                         @"term": searchQueryStr,
                                         @"category_filter":categoryFilterStr,
                                         @"ll": searchLocationStr,
                                         @"radius_filter": radiusFilterStr,
                                         @"limit": SearchLimit
                                         };
                
                NSURLRequest *searchRequest = [NSURLRequest requestWithHost:APIHost
                                                                       path:SearchPath
                                                                     params:params
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
                                                  if(!m_cancelled)
                                                  {
                                                      m_completionCallback();
                                                  }
                                                  
                                                  Eegeo_DELETE this;
                                              });
                           }];
                
                [m_pTask resume];
            }
            
            void iOSYelpSearchQuery::Cancel()
            {
                Eegeo_ASSERT(m_pTask != NULL, "Cannot cancel iOSYelpSearchQuery until query has been dispatched.\n");
                m_cancelled = true;
                [m_pTask cancel];
            }
            
            bool iOSYelpSearchQuery::IsSucceeded()
            {
                return m_isSuccess;
            }
            
            const std::string& iOSYelpSearchQuery::ResponseString()
            {
                return m_responseString;
            }
            
            const SdkModel::SearchQuery& iOSYelpSearchQuery::GetSearchQuery() const
            {
                return m_searchQuery;
            }
        }
    }
}
