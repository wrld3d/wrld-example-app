// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapModule.h"
#include "Search.h"
#include "SearchResultOnMap.h"
#include "SearchResultOnMapFactory.h"
#include "SearchResultOnMapModel.h"
#include "SearchResultMyPinsService.h"
#include "SearchResultOnMapItemModelSelectedObserver.h"
#include "IIdentity.h"
#include "IWorldPinsService.h"
#include "IMyPinsService.h"
#include "ISearchResultIconKeyMapper.h"
#include "ISearchResultRepository.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace SdkModel
        {
            void SearchResultOnMapModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<View::SearchResultOnMapFactory>().as<View::ISearchResultOnMapFactory>().singleInstance();
                builder->registerType<SearchResultOnMapModel>().as<ISearchResultOnMapModel>().singleInstance();
                builder->registerType<View::SearchResultOnMapItemModelSelectedObserver>().singleInstance();
            }
            
            void SearchResultOnMapModule::RegisterLeaves()
            {
                RegisterLeaf<View::SearchResultOnMapItemModelSelectedObserver>();
                RegisterLeaf<ISearchResultOnMapModel>();
            }
        }
    }
}
