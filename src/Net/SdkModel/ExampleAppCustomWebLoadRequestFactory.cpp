// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleAppCustomWebLoadRequestFactory.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            ExampleAppCustomWebLoadRequestFactory::ExampleAppCustomWebLoadRequestFactory(Eegeo::Helpers::IHttpCache& httpCache,
                                                                                         Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                                                                         INetworkCapabilities& networkCapabilities)
            : m_httpCache(httpCache)
            , m_webLoadRequestFactory(webLoadRequestFactory)
            , m_networkCapabilities(networkCapabilities)
            {
                
            }
            
            Eegeo::Web::IWebLoadRequest* ExampleAppCustomWebLoadRequestFactory::CreateGet(std::string url,
                                                                                          Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                                          void* userData,
                                                                                          const std::string* pUserAgent)
            {
                if(CanStream(false, url))
                {
                    return m_webLoadRequestFactory.CreateGet(url, callback, userData, pUserAgent);
                }
                return new OfflineWebLoadRequest(false, url, callback, userData);
            }
            
            Eegeo::Web::IWebLoadRequest* ExampleAppCustomWebLoadRequestFactory::CreateGet(std::string url,
                                                                                          Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                                          void* userData,
                                                                                          const std::map<std::string, std::string>& headers,
                                                                                          const std::string* pUserAgent)
            {
                if(CanStream(false, url))
                {
                    return m_webLoadRequestFactory.CreateGet(url, callback, userData, headers, pUserAgent);
                }
                return new OfflineWebLoadRequest(false, url, callback, userData);
            }
            
            Eegeo::Web::IWebLoadRequest* ExampleAppCustomWebLoadRequestFactory::CreateSynchronousGet(std::string url,
                                                                                                     Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                                                     void* userData,
                                                                                                     const std::string* pUserAgent)
            {
                if (CanStream(false, url))
                {
                    return m_webLoadRequestFactory.CreateSynchronousGet(url, callback, userData, pUserAgent);
                }
                return new OfflineWebLoadRequest(false, url, callback, userData);
            }
            
            Eegeo::Web::IWebLoadRequest* ExampleAppCustomWebLoadRequestFactory::CreatePost(std::string url,
                                                                                           Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                                           void* userData,
                                                                                           const std::map<std::string, std::string>& postData,
                                                                                           const std::string* pUserAgent)
            {
                if(CanStream(true, url))
                {
                    return m_webLoadRequestFactory.CreatePost(url, callback, userData, postData, pUserAgent);
                }
                return new OfflineWebLoadRequest(true, url, callback, userData);
            }
            
            Eegeo::Web::IWebLoadRequest* ExampleAppCustomWebLoadRequestFactory::CreatePost(std::string url,
                                                                                           Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                                           void* userData,
                                                                                           const std::map<std::string, std::string>& postData,
                                                                                           const std::map<std::string, std::string>& headers,
                                                                                           const std::string* pUserAgent)
            {
                if(CanStream(true, url))
                {
                    return m_webLoadRequestFactory.CreatePost(url, callback, userData, postData, headers, pUserAgent);
                }
                
                return new OfflineWebLoadRequest(true, url, callback, userData);
            }
            
            
            Eegeo::Web::IWebLoadRequest* ExampleAppCustomWebLoadRequestFactory::CreatePost(std::string url,
                                                                                           Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                                           void* userData,
                                                                                           const std::map<std::string, std::string>& postData,
                                                                                           const std::map<std::string, std::string>& headers,
                                                                                           const std::map<std::string, Eegeo::Web::ImageUploadData>& imageData,
                                                                                           const std::string* pUserAgent)
            {
                if(CanStream(true, url))
                {
                    return m_webLoadRequestFactory.CreatePost(url, callback, userData, postData, headers, imageData, pUserAgent);
                }
                
                return new OfflineWebLoadRequest(true, url, callback, userData);
            }
            
            bool ExampleAppCustomWebLoadRequestFactory::CanStream(bool isPost, std::string& url)
            {
                if(m_networkCapabilities.StreamOverWifiOnly())
                {
                    if(m_networkCapabilities.ConnectedToWifi())
                    {
                        return true;
                    }
                    
                    if(isPost)
                    {
                        return false;
                    }
                    
                    return m_httpCache.IsInCache(url);
                }
                else if(!m_networkCapabilities.NetworkAvailable())
                {
                    if(isPost)
                    {
                        return false;
                    }
                    
                    return m_httpCache.IsInCache(url);
                }
                
                return true;
            }
        }
    }
}
