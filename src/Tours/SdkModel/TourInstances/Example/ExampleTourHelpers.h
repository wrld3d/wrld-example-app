// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Tours.h"
#include "Search.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    Search::SdkModel::SearchResultModel CreateSearchResultModelFromTourStateModel(const TourStateModel& model);
                    
                    std::string CreateJsonDataFromTourStateModel(const TourStateModel& model);
                }
            }
        }
    }
}