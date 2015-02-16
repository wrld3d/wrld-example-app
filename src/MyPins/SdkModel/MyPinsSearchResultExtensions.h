// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Search.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            bool TryFindPinnedPoiForSearchResult(MyPins::SdkModel::IMyPinsRepository& myPinsRepository,
                                                 const Search::SdkModel::SearchResultModel& searchResult,
                                                 MyPins::SdkModel::MyPinModel*& out_pMyPinModel);
        }
    }
}
