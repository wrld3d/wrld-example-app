// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPlatformAbstractionModule.h"
#include "ExampleAppCustomWebLoadRequestFactory.h"
#include "NetIncludes.h"
#include "Tasks.h"
#include "SceneBuilderModuleFactory.h"

namespace ExampleApp
{
    class PlatformAbstractionsFacade: public Eegeo::Modules::IPlatformAbstractionModule, private Eegeo::NonCopyable
    {
    private:
        Eegeo::Modules::IPlatformAbstractionModule& m_wrappedPlatformAbstractions;
        Net::SdkModel::ExampleAppCustomWebLoadRequestFactory* m_pWebLoadRequestFactory;
        Net::SdkModel::ExampleAppCustomWebLoadRequestFactory* m_pPlatformWebLoadRequestFactory;

        Eegeo::Modules::SceneBuilderModuleFactory m_sceneBuilderModuleFactory;
        
    public:
        PlatformAbstractionsFacade(Eegeo::Modules::IPlatformAbstractionModule& wrappedPlatformAbstractions,
                                   Net::SdkModel::INetworkCapabilities& networkCapabilities);
        
        ~PlatformAbstractionsFacade();
        
        Eegeo::Helpers::ITextureFileLoader& GetTextureFileLoader() const;
        Eegeo::Web::IWebLoadRequestFactory& GetWebLoadRequestFactory() const;
        Eegeo::Web::IWebLoadRequestFactory& GetPlatformWebLoadRequestFactory() const;
        Eegeo::Web::IWebProxySettings& GetProxySettings() const;
        Eegeo::Web::ISSLSettings& GetSSLSettings() const;
        Eegeo::Helpers::IHttpCache& GetHttpCache() const;
        Eegeo::Helpers::IFileIO& GetFileIO() const;
        Eegeo::Helpers::UrlHelpers::IUrlEncoder& GetUrlEncoder() const;
        Eegeo::Web::IConnectivityService& GetConnectivityService() const;
        Eegeo::Concurrency::Tasks::IWorkPool& GetWorkPool() const;
        Eegeo::Modules::ISceneBuilderModuleFactory& GetSceneBuilderModuleFactory();
        Eegeo::Rendering::AsyncTexturing::ITextureFactory& GetTextureFactory() const;
       
        void OnPause();
        void Update();
        void OnResume();
    };
}
