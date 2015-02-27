// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "MyPins.h"
#include "Search.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class IMyPinDetailsDisplayService
            {
            public:
                virtual ~IMyPinDetailsDisplayService() { }
                
                virtual void DisplayUserCreatedMyPinDetails(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                            const std::string& title,
                                                            const std::string& description,
                                                            const std::string& imagePath) = 0;
                
                virtual void DisplaySearchResultMyPinDetails(const Search::SdkModel::SearchResultModel& searchResultModel) = 0;
            };
        }
    }
}
