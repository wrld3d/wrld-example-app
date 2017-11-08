// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "TagSearchModelFactory.h"
#include "ApplicationConfigurationJsonParser.h"
#include "document.h"
#include "Types.h"
#include "FileHelpers.h"
#include "YelpCategoryMapperUpdater.h"
#include "YelpCategoryModel.h"


namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            namespace
            {
                void CreateModels(const std::vector<ExampleApp::ApplicationConfig::SdkModel::ApplicationMenuItemTagSearchConfig> menuItems, std::vector<ExampleApp::TagSearch::View::TagSearchModel>& out_models, Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater)
                {
                    out_models = std::vector<ExampleApp::TagSearch::View::TagSearchModel>();
                    for(auto iter = menuItems.cbegin(); iter != menuItems.cend(); iter++) {
                        if (iter->skipYelp) {
                            Search::Yelp::SdkModel::YelpCategoryModel yelpCategoryModel{
                                    "unused_string", true};
                            yelpCategoryMapperUpdater.AddMapping(iter->searchTag,
                                                                 yelpCategoryModel);
                        } else if (iter->yelpMapping.length() > 0 && iter->yelpMapping != "unused_string") {
                            Search::Yelp::SdkModel::YelpCategoryModel yelpCategoryModel{
                                    iter->yelpMapping, false};
                            yelpCategoryMapperUpdater.AddMapping(iter->searchTag,
                                                                 yelpCategoryModel);
                        }

                        const bool visibleInSearchMenu = true;
                        const bool interior = true;

                        // TODO: do parsing for extended options, such as is_interior? and radius searching. This needs
                        // looked at in conjunction with other apps.
                        out_models.push_back(
                                TagSearchModel(iter->name, iter->searchTag, interior, iter->iconKey, visibleInSearchMenu)
                        );
                    }
                }
            }

            std::vector<TagSearch::View::TagSearchModel> CreateTagSearchModelsFromConfig(const ApplicationConfig::ApplicationConfiguration& applicationConfig, const std::string& jsonAttributeName, Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater)
            {
                std::vector<ExampleApp::TagSearch::View::TagSearchModel> result;
                CreateModels(applicationConfig.OutdoorSearchMenuItems(), result, yelpCategoryMapperUpdater);
                return result;
            }
        }
    }
}
