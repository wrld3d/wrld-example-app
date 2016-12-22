// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



#include "YelpCategoryMapperUpdater.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpCategoryMapperUpdater::YelpCategoryMapperUpdater()
                {
                }
                
                void YelpCategoryMapperUpdater::RegisterMappingAdded(Eegeo::Helpers::ICallback2<const std::string, const YelpCategoryModel>& callback)
                {
                    m_callbacks.AddCallback(callback);
                }
                
                void YelpCategoryMapperUpdater::UnregisterMappingAdded(Eegeo::Helpers::ICallback2<const std::string, const YelpCategoryModel>& callback)
                {
                    m_callbacks.RemoveCallback(callback);
                }
                
                void YelpCategoryMapperUpdater::AddMapping(const std::string& tag, const YelpCategoryModel& yelpCategoryModel)
                {
                    m_callbacks.ExecuteCallbacks(tag, yelpCategoryModel);
                }
                
                void YelpCategoryMapperUpdater::RegisterMappingReset(Eegeo::Helpers::ICallback0& callback)
                {
                    m_callbacks0.AddCallback(callback);
                }
                
                void YelpCategoryMapperUpdater::UnregisterMappingReset(Eegeo::Helpers::ICallback0& callback)
                {
                    m_callbacks0.RemoveCallback(callback);
                }
                
                void YelpCategoryMapperUpdater::ResetMapping()
                {
                    m_callbacks0.ExecuteCallbacks();
                }
            }
        }
    }
}
