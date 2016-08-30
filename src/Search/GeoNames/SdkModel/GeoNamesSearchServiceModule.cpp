// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesSearchServiceModule.h"

#include "GeoNamesJsonParser.h"
#include "GeoNamesSearchQueryFactory.h"
#include "GeoNamesSearchService.h"
#include "IWebLoadRequestFactory.h"
#include "INetworkCapabilities.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchServiceModule::GeoNamesSearchServiceModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
                : m_builder(builder)
                {
                }
                
                void GeoNamesSearchServiceModule::Register()
                {
                    m_builder->registerType<GeoNamesJsonParser>().as<IGeoNamesParser>().singleInstance();
                    m_builder->registerType<GeoNamesSearchQueryFactory>().as<IGeoNamesSearchQueryFactory>().singleInstance();
                    m_builder->registerType<GeoNamesSearchService>().singleInstance();
                }
            }
        }
    }
}
