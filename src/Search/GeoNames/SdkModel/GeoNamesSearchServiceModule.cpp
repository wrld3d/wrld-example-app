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
                void GeoNamesSearchServiceModule::Register(const TContainerBuilder& builder)
                {
                    builder->registerType<GeoNamesJsonParser>().as<IGeoNamesParser>().singleInstance();
                    builder->registerType<GeoNamesSearchQueryFactory>().as<IGeoNamesSearchQueryFactory>().singleInstance();
                    builder->registerType<GeoNamesSearchService>().singleInstance();
                }
            }
        }
    }
}
