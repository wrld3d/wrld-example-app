// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsDisplayService.h"
#include "MyPinModel.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsDisplayService::MyPinDetailsDisplayService(IMyPinDetailsViewModel& myPinDetailsViewModel,
                                                                   SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            : m_myPinDetailsViewModel(myPinDetailsViewModel)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            {
                
            }
            
            MyPinDetailsDisplayService::~MyPinDetailsDisplayService()
            
            {
                
            }
            
            
            void MyPinDetailsDisplayService::DisplayUserCreatedMyPinDetails(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                                            const std::string& title,
                                                                            const std::string& description,
                                                                            const std::string& imagePath)
            {
                if (!m_myPinDetailsViewModel.IsOpen())
                {
                    m_myPinDetailsViewModel.Open(pinId, title, description, imagePath);
                }
            }
            
            void MyPinDetailsDisplayService::DisplaySearchResultMyPinDetails(const Search::SdkModel::SearchResultModel& searchResultModel)
            {
                if (!m_searchResultPoiViewModel.IsOpen())
                {
                    m_searchResultPoiViewModel.Open(searchResultModel, true);
                }
            }
        }
    }
}
