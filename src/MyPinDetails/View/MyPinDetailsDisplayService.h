// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMyPinDetailsDisplayService.h"
#include "IMyPinDetailsViewModel.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {   
            class MyPinDetailsDisplayService : public IMyPinDetailsDisplayService, private Eegeo::NonCopyable
            {
                IMyPinDetailsViewModel& m_myPinDetailsViewModel;
                SearchResultPoi::View::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
                
            public:
                MyPinDetailsDisplayService(IMyPinDetailsViewModel& myPinDetailsViewModel,
                                           SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel);
                
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
