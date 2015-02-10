// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include "Types.h"
#include "Web.h"
#include "IHttpCache.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            class ExampleAppCustomWebLoadRequestFactory : public Eegeo::Web::IWebLoadRequestFactory
            {
                Eegeo::Helpers::IHttpCache& m_httpCache;
                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
                INetworkCapabilities& m_networkCapabilities;
                
            public:
                ExampleAppCustomWebLoadRequestFactory(Eegeo::Helpers::IHttpCache& httpCache,
                                                      Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory,
                                                      INetworkCapabilities& networkCapabilities);
                
                
                Eegeo::Web::IWebLoadRequest* CreateGet(std::string url,
                                                       Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                       void* userData,
                                                       const std::string* pUserAgent=NULL);
                
                Eegeo::Web::IWebLoadRequest* CreateGet(std::string url,
                                                       Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                       void* userData,
                                                       const std::map<std::string, std::string>& headers,
                                                       const std::string* pUserAgent=NULL);
                
                Eegeo::Web::IWebLoadRequest* CreateSynchronousGet(std::string url,
                                                                  Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                                  void* userData,
                                                                  const std::string* pUserAgent=NULL);
                
                Eegeo::Web::IWebLoadRequest* CreatePost(std::string url,
                                                        Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                        void* userData,
                                                        const std::map<std::string, std::string>& postData,
                                                        const std::string* pUserAgent=NULL);
                
                Eegeo::Web::IWebLoadRequest* CreatePost(std::string url,
                                                        Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                        void* userData,
                                                        const std::map<std::string, std::string>& postData,
                                                        const std::map<std::string, std::string>& headers,
                                                        const std::string* pUserAgent=NULL);
                
                Eegeo::Web::IWebLoadRequest* CreatePost(std::string url,
                                                        Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                                        void* userData,
                                                        const std::map<std::string, std::string>& postData,
                                                        const std::map<std::string, std::string>& headers,
                                                        const std::map<std::string, Eegeo::Web::ImageUploadData>& imageData,
                                                        const std::string* pUserAgent=NULL);
                
            private:
                bool CanStream(bool isPost, std::string& url);
                
                class OfflineWebLoadRequest : public Eegeo::Web::IWebLoadRequest, protected Eegeo::NonCopyable
                {
                    std::string m_url;
                    bool m_post;
                    TResourceData m_empty;
                    void* m_userData;
                    Eegeo::Web::IWebLoadRequestCompletionCallback& m_callback;
                    bool m_cancelled;
                    
                public:
                    OfflineWebLoadRequest(bool post,
                                          std::string url,
                                          Eegeo::Web::IWebLoadRequestCompletionCallback& callback,
                                          void* userData)
                    : IWebLoadRequest(url, callback, userData)
                    ,m_url(url)
                    ,m_post(post)
                    ,m_callback(callback)
                    ,m_userData(userData)
                    ,m_cancelled(false)
                    {
                        
                    }
                    
                    ~OfflineWebLoadRequest() { }
                    
                    void Load() { if(!m_cancelled) { m_callback(*this); } }
                    void Cancel() { m_cancelled = true; }
                    virtual bool IsLoading() const { return true; }
                    virtual bool IsSucceeded() const { return false; }
                    virtual bool IsErrored() const { return true; }
                    virtual bool IsCancelled() const { return m_cancelled; }
                    virtual std::string HttpMethod() const { return m_post ? "POST" :"GET"; }
                    virtual int HttpStatusCode() const { return -1; };
                    virtual std::string GetUrl() const { return m_url; }
                    virtual void* GetUserData() const { return m_userData; }
                    virtual const TResourceData& GetHeaderData() const { return m_empty; }
                    virtual const TResourceData& GetResourceData() const { return m_empty; }
                    virtual const TResourceData* TransferResourceDataOwnership() { return Eegeo_NEW(TResourceData); }
                    virtual size_t GetPreDecompressBytesRead() const { return 0; }
                    virtual void SetTimeoutSeconds(uint timeoutSeconds) { ; }
                    virtual void TryToUpdateResourceIfModified() { ; }
                    virtual void SetNumRetries(u32 retries) { ; }
                };
            };
        }
    }
}


