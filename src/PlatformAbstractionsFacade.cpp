// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlatformAbstractionsFacade.h"
#include "IConnectivityService.h"

namespace ExampleApp
{
    PlatformAbstractionsFacade::PlatformAbstractionsFacade(Eegeo::Modules::IPlatformAbstractionModule& wrappedPlatformAbstractions,
                                                           Net::SdkModel::INetworkCapabilities& networkCapabilities)
    : m_wrappedPlatformAbstractions(wrappedPlatformAbstractions)
    , m_pWebLoadRequestFactory(NULL)
    , m_pPlatformWebLoadRequestFactory(NULL)
    {
        
        m_pWebLoadRequestFactory = Eegeo_NEW(ExampleApp::Net::SdkModel::ExampleAppCustomWebLoadRequestFactory)(wrappedPlatformAbstractions.GetWebLoadRequestFactory(),
                                                                                                               networkCapabilities);
        
        m_pPlatformWebLoadRequestFactory = Eegeo_NEW(ExampleApp::Net::SdkModel::ExampleAppCustomWebLoadRequestFactory)(wrappedPlatformAbstractions.GetPlatformWebLoadRequestFactory(),
                                                                                                                       networkCapabilities);
    }
    
    PlatformAbstractionsFacade::~PlatformAbstractionsFacade()
    {
        Eegeo_DELETE m_pPlatformWebLoadRequestFactory;
        Eegeo_DELETE m_pWebLoadRequestFactory;
    }
    
    Eegeo::Helpers::ITextureFileLoader& PlatformAbstractionsFacade::GetTextureFileLoader() const
    {
        return m_wrappedPlatformAbstractions.GetTextureFileLoader();
    }
    
    Eegeo::Web::IWebLoadRequestFactory& PlatformAbstractionsFacade::GetWebLoadRequestFactory() const
    {
        return *m_pWebLoadRequestFactory;
    }
    
    Eegeo::Web::IWebLoadRequestFactory& PlatformAbstractionsFacade::GetPlatformWebLoadRequestFactory() const
    {
        return *m_pPlatformWebLoadRequestFactory;
    }
    
    Eegeo::Web::IWebProxySettings& PlatformAbstractionsFacade::GetProxySettings() const
    {
        return m_wrappedPlatformAbstractions.GetProxySettings();
    }
    
    Eegeo::Web::ISSLSettings& PlatformAbstractionsFacade::GetSSLSettings() const
    {
        return m_wrappedPlatformAbstractions.GetSSLSettings();
    }
    
    Eegeo::Helpers::IHttpCache& PlatformAbstractionsFacade::GetHttpCache() const
    {
        return m_wrappedPlatformAbstractions.GetHttpCache();
    }
    
    Eegeo::Helpers::IFileIO& PlatformAbstractionsFacade::GetFileIO() const
    {
        return m_wrappedPlatformAbstractions.GetFileIO();
    }
    
    Eegeo::Helpers::UrlHelpers::IUrlEncoder& PlatformAbstractionsFacade::GetUrlEncoder() const
    {
        return m_wrappedPlatformAbstractions.GetUrlEncoder();
    }
    
    Eegeo::Web::IConnectivityService& PlatformAbstractionsFacade::GetConnectivityService() const
    {
        return m_wrappedPlatformAbstractions.GetConnectivityService();
    }
    
    Eegeo::Concurrency::Tasks::IWorkPool& PlatformAbstractionsFacade::GetWorkPool() const
    {
        return m_wrappedPlatformAbstractions.GetWorkPool();
    }
    
    void PlatformAbstractionsFacade::OnPause()
    {
        return m_wrappedPlatformAbstractions.OnPause();
    }
    
    void PlatformAbstractionsFacade::Update()
    {
        return m_wrappedPlatformAbstractions.Update();
    }
    
    void PlatformAbstractionsFacade::OnResume()
    {
        return m_wrappedPlatformAbstractions.OnResume();
    }

    Eegeo::Modules::ISceneBuilderModuleFactory& PlatformAbstractionsFacade::GetSceneBuilderModuleFactory()
    {
        return m_sceneBuilderModuleFactory;
    }

    Eegeo::Rendering::AsyncTexturing::ITextureFactory& PlatformAbstractionsFacade::GetTextureFactory() const
    {
        return m_wrappedPlatformAbstractions.GetTextureFactory();
    }
}
