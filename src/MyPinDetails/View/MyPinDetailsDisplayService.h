// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMyPinDetailsDisplayService.h"
#include "IMyPinDetailsViewModel.h"
#include "SearchResultPoi.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {   
            class MyPinDetailsDisplayService : public IMyPinDetailsDisplayService, private Eegeo::NonCopyable
            {
                const std::shared_ptr<IMyPinDetailsViewModel> m_myPinDetailsViewModel;
                const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel> m_searchResultPoiViewModel;
                const std::shared_ptr<const Menu::View::IMenuReactionModel> m_menuReaction;
                
            public:
                MyPinDetailsDisplayService(const std::shared_ptr<IMyPinDetailsViewModel>& myPinDetailsViewModel,
                                           const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel>& searchResultPoiViewModel,
                                           const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReactionModel);
                
                ~MyPinDetailsDisplayService();
                
                void DisplayUserCreatedMyPinDetails(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                    const std::string& title,
                                                    const std::string& description,
                                                    const std::string& imagePath);
                
                void DisplaySearchResultMyPinDetails(const Search::SdkModel::SearchResultModel& searchResultModel);
            };
        }
    }
}
