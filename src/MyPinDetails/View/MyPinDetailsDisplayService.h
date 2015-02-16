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
                
                void CreateSearchResultModelFromPinModel(const MyPins::SdkModel::MyPinModel& myPinModel,
                                                         Search::SdkModel::SearchResultModel& out_searchResultModel);
                
            public:
                MyPinDetailsDisplayService(IMyPinDetailsViewModel& myPinDetailsViewModel,
                                           SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel);
                
                ~MyPinDetailsDisplayService();
                
                virtual void DisplayPinDetails(const MyPins::SdkModel::MyPinModel& myPinModel);
            };
        }
    }
}
