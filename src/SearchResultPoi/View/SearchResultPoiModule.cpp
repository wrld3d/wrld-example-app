// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"
#include "DesktopSearchResultPoiViewModel.h"
#include "SearchResultPoiMyPinService.h"
#include "SearchResultPoiViewImageFetcher.h"
#include "SearchResultPoiPinToggledMessageHandler.h"
#include "SearchResultPoiViewOpenedMessageHandler.h"
#include "IReactionControllerModel.h"
#include "IMyPinsService.h"
#include "ISearchResultMyPinsService.h"
#include "IWebLoadRequestFactory.h"
#include "SearchResultPoiController.h"
#include "ISearchResultIconKeyMapper.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            void SearchResultPoiModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<DesktopSearchResultPoiViewModel>().as<ISearchResultPoiViewModel>().singleInstance();
                builder->registerType<SearchResultPoiViewModel>().as<ISearchResultPoiViewModel>().singleInstance();
                builder->registerType<SdkModel::SearchResultPoiMyPinService>().as<SdkModel::ISearchResultPoiMyPinService>().singleInstance();
                builder->registerType<SdkModel::SearchResultPoiPinToggledMessageHandler>().singleInstance();
                builder->registerType<SdkModel::SearchResultPoiViewImageFetcher>().as<SdkModel::ISearchResultPoiViewImageFetcher>().singleInstance();
                builder->registerType<SdkModel::SearchResultPoiViewOpenedMessageHandler>().singleInstance();
                builder->registerType<View::SearchResultPoiController>().singleInstance();
            }
            
            void SearchResultPoiModule::RegisterLeaves()
            {
                RegisterLeaf<SdkModel::SearchResultPoiPinToggledMessageHandler>();
                RegisterLeaf<SdkModel::SearchResultPoiViewOpenedMessageHandler>();
                RegisterLeaf<View::SearchResultPoiController>();
            }
        }
    }
}
