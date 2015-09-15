// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IRepositoryModel.h"
#include "TourModel.h"
#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class ITourRepository : public Repository::IRepositoryModel<TourModel>
            {
            public:
                virtual ~ITourRepository() { }
                
                virtual bool ContainsTourModelWithName(const std::string& name) = 0;
                
                virtual TourModel GetTourModelWithName(const std::string& name) = 0;
            };
        }
    }
}
