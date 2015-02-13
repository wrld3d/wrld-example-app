// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "MyPinsSearchResultExtensions.h"
#include "IMyPinsRepository.h"
#include "SearchResultModel.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            bool TryFindPinnedPoiForSearchResult(MyPins::SdkModel::IMyPinsRepository& myPinsRepository,
                                                 const Search::SdkModel::SearchResultModel& searchResult,
                                                 MyPins::SdkModel::MyPinModel*& out_pMyPinModel)
            {
                for(size_t i = 0; i < myPinsRepository.GetItemCount(); ++ i)
                {
                    MyPins::SdkModel::MyPinModel& myPinModel = *myPinsRepository.GetItemAtIndex(i);
                    
                    if(myPinModel.GetSemanticPinType() == MyPins::SdkModel::SearchResultPoi)
                    {
                        const std::string& json = myPinModel.GetTypeMetadata();
                        const Search::SdkModel::SearchResultModel myPinSearchResultModel = Search::SdkModel::DeserializeFromJson(json);
                        
                        if(searchResult == myPinSearchResultModel)
                        {
                            out_pMyPinModel = &myPinModel;
                            return true;
                        }
                    }
                }
                
                out_pMyPinModel = NULL;
                return false;
            }
        }
    }
}
