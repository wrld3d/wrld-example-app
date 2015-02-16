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
            
            void MyPinDetailsDisplayService::DisplayPinDetails(const MyPins::SdkModel::MyPinModel& myPinModel)
            {
                switch(myPinModel.GetSemanticPinType())
                {
                    case MyPins::SdkModel::UserCreatedPoi:
                    {
                        if (!m_myPinDetailsViewModel.IsOpen())
                        {
                            m_myPinDetailsViewModel.Open(myPinModel);
                        }
                    }break;
                        
                    case MyPins::SdkModel::SearchResultPoi:
                    {
                        if (!m_searchResultPoiViewModel.IsOpen())
                        {
                            Search::SdkModel::SearchResultModel searchResultModel;
                            CreateSearchResultModelFromPinModel(myPinModel, searchResultModel);
                            m_searchResultPoiViewModel.Open(searchResultModel, true);
                        }
                    }break;
                        
                    default:
                    {
                        Eegeo_ASSERT(false, "Unknown pin type selected.\n");
                    }break;
                }
            }
            
            void MyPinDetailsDisplayService::CreateSearchResultModelFromPinModel(const MyPins::SdkModel::MyPinModel& myPinModel,
                                                                                 Search::SdkModel::SearchResultModel& out_searchResultModel)
            {
                Eegeo_ASSERT(myPinModel.GetSemanticPinType() == MyPins::SdkModel::SearchResultPoi);
                out_searchResultModel = Search::SdkModel::DeserializeFromJson(myPinModel.GetTypeMetadata());
            }
        }
    }
}
