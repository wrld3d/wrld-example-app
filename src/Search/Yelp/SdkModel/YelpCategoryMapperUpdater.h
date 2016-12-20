// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Helpers.h"
#include "CallbackCollection.h"
#include "YelpCategoryModel.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpCategoryMapperUpdater : private Eegeo::NonCopyable
                {
                public:
                    YelpCategoryMapperUpdater();
                    
                    void RegisterMappingAdded(Eegeo::Helpers::ICallback2<const std::string, const YelpCategoryModel>& callback);
                    void UnregisterMappingAdded(Eegeo::Helpers::ICallback2<const std::string, const YelpCategoryModel>& callback);
                    void AddMapping(const std::string& tag, const YelpCategoryModel& yelpCategoryModel);
                private:
                    Eegeo::Helpers::CallbackCollection2<const std::string, const YelpCategoryModel> m_callbacks;
                    
                };
            }
        }
    }
}