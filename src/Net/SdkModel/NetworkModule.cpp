// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NetworkModule.h"
#include "ConnectivityChangedObserver.h"
#include "NavigationService.h"
#include "ILocationService.h"
#include "TerrainHeightProvider.h"
#include "WebConnectivityValidator.h"
#include "NetworkCapabilities.h"
#include "IPersistentSettingsModel.h"

namespace ExampleApp
{
    namespace Net
    {
        namespace SdkModel
        {
            void NetworkModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<ExampleApp::Net::SdkModel::NetworkCapabilities>().as<ExampleApp::Net::SdkModel::INetworkCapabilities>().singleInstance();
                builder->registerType<ConnectivityChangedObserver>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<Eegeo::Location::NavigationService>(
                                                                                                                   context.resolve<Eegeo::Location::ILocationService>().get(),
                                                                                                                   context.resolve<Eegeo::Resources::Terrain::Heights::TerrainHeightProvider>().get()
                                                                                                                   );
                                                   }).singleInstance();
            }
            
            void NetworkModule::RegisterNativeLeaves()
            {
                RegisterLeaf<ConnectivityChangedObserver>();
            }
        }
    }
}
