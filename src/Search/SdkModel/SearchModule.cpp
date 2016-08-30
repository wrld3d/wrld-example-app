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

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchModule::SearchModule(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
            : m_builder(builder)
            {
            }
            
            void SearchModule::Register()
            {
                Search::GeoNames::SdkModel::GeoNamesSearchServiceModule(m_builder).Register();
                Search::EegeoPois::SdkModel::EegeoSearchServiceModule(m_builder).Register();
                ExampleApp::Search::Yelp::YelpSearchServiceModule(m_builder).Register();
                m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       std::map<std::string, std::shared_ptr<Search::SdkModel::ISearchService>> searchServices;
                                                       searchServices[Search::GeoNamesVendorName] = context.resolve<ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService>();
                                                       searchServices[Search::EegeoVendorName] = context.resolve<ExampleApp::Search::EegeoPois::SdkModel::EegeoSearchService>();
                                                       searchServices[Search::YelpVendorName] = context.resolve<ExampleApp::Search::Yelp::SdkModel::YelpSearchService>();
                                                       return std::make_shared<ExampleApp::Search::Combined::SdkModel::CombinedSearchService>(searchServices,
                                                                                                                                              context.resolve<Eegeo::Resources::Interiors::InteriorInteractionModel>());
                                                       
                                                   }).as<Search::SdkModel::ISearchService>().singleInstance();
                m_builder->registerType<SearchResultRepository>().as<ISearchResultRepository>().singleInstance();
                m_builder->registerType<MyPins::SearchResultMyPinsService>().as<MyPins::ISearchResultMyPinsService>().singleInstance();
                m_builder->registerType<MyPins::MyPinsSearchResultRefreshService>().as<MyPins::IMyPinsSearchResultRefreshService>().singleInstance();
                m_builder->registerType<SearchQueryPerformer>().as<ISearchQueryPerformer>().singleInstance();
                m_builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                                   {
                                                       return std::make_shared<SearchRefreshService>(context.resolve<ISearchService>(),
                                                                                                     context.resolve<ISearchQueryPerformer>(),
                                                                                                     context.resolve<CameraTransitions::SdkModel::ICameraTransitionController>(),
                                                                                                     context.resolve<Eegeo::Resources::Interiors::InteriorInteractionModel>(),
                                                                                                     1.f,
                                                                                                     100.f,
                                                                                                     1100.f,
                                                                                                     50.f);
                                                   }).as<ISearchRefreshService>().singleInstance();\
                m_builder->registerType<SearchQueryObserver>().singleInstance();
            }
        }
    }
}
