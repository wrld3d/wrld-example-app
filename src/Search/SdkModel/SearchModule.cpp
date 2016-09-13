// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchModule.h"
#include "SearchResultRepository.h"
#include "SearchResultModel.h"
#include "SearchQueryPerformer.h"
#include "SearchQueryObserver.h"
#include "SearchRefreshService.h"
#include "SearchResultMyPinsService.h"
#include "MyPinsSearchResultRefreshService.h"
#include "GeoNamesSearchServiceModule.h"
#include "EegeoSearchServiceModule.h"
#include "YelpSearchServiceModule.h"
#include "GeoNamesSearchService.h"
#include "EegeoSearchService.h"
#include "YelpSearchService.h"
#include "CombinedSearchService.h"
#include "SearchVendorNames.h"
#include "IGeoNamesSearchQueryFactory.h"
#include "IGeoNamesParser.h"
#include "INetworkCapabilities.h"
#include "InteriorInteractionModel.h"
#include "ICameraTransitionController.h"
#include "IEegeoSearchQueryFactory.h"
#include "IEegeoParser.h"
#include "YelpSearchQueryFactory.h"
#include "YelpBusinessQueryFactory.h"
#include "YelpBusinessJsonParser.h"
#include "IYelpCategoryToTagMapper.h"
#include "ISearchResultParser.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            void SearchModule::Register(const TContainerBuilder& builder)
            {
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       std::map<std::string, std::shared_ptr<Search::SdkModel::ISearchService>> searchServices;
                                                       searchServices[Search::GeoNamesVendorName] = context.resolve<ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService>();
                                                       searchServices[Search::EegeoVendorName] = context.resolve<ExampleApp::Search::EegeoPois::SdkModel::EegeoSearchService>();
                                                       searchServices[Search::YelpVendorName] = context.resolve<ExampleApp::Search::Yelp::SdkModel::YelpSearchService>();
                                                       return std::make_shared<ExampleApp::Search::Combined::SdkModel::CombinedSearchService>(searchServices,
                                                                                                                                              context.resolve<Eegeo::Resources::Interiors::InteriorInteractionModel>());
                                                       
                                                   }).as<Search::SdkModel::ISearchService>().singleInstance();
                builder->registerType<SearchResultRepository>().as<ISearchResultRepository>().singleInstance();
                builder->registerType<MyPins::SearchResultMyPinsService>().as<MyPins::ISearchResultMyPinsService>().singleInstance();
                builder->registerType<MyPins::MyPinsSearchResultRefreshService>().as<MyPins::IMyPinsSearchResultRefreshService>().singleInstance();
                builder->registerType<SearchQueryPerformer>().as<ISearchQueryPerformer>().singleInstance();
                builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<SearchRefreshService>(context.resolve<ISearchService>(),
                                                                                                     context.resolve<ISearchQueryPerformer>(),
                                                                                                     context.resolve<CameraTransitions::SdkModel::ICameraTransitionController>(),
                                                                                                     context.resolve<Eegeo::Resources::Interiors::InteriorInteractionModel>(),
                                                                                                     1.f,
                                                                                                     100.f,
                                                                                                     1100.f,
                                                                                                     50.f);
                                                   }).as<ISearchRefreshService>().singleInstance();
                builder->registerType<SearchQueryObserver>().singleInstance();
            }
            
            void SearchModule::RegisterLeaves()
            {
                RegisterLeaf<SearchQueryObserver>();
            }
        }
    }
}
