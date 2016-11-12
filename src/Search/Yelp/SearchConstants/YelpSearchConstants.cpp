// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchConstants.h"
#include "document.h"
#include "FileHelpers.h"
#include "Types.h"


//
// Yelp categories from http://www.yelp.com/developers/documentumentation/v2/all_category_list
//

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SearchConstants
            {
                namespace
                {
                    void ParseYelpFoundationCategoryToApplicationTagMap(
                            const rapidjson::Document& document,
                            const std::vector<std::string>& appTags,
                            std::map<std::string, std::string>& out_yelpFoundationCategoryToAppTag)
                    {
                        const char* appTagToYelpCategoriesKey = "app_tag_to_yelp_leaf_categories";

                        Eegeo_ASSERT(document.HasMember(appTagToYelpCategoriesKey),
                                "Key doesn't exist: %s\n", appTagToYelpCategoriesKey)

                        const auto& appTagToYelpCategoriesJsonObj = document[appTagToYelpCategoriesKey];

                        for (std::vector<std::string>::const_iterator appTagIter = appTags.begin();
                             appTagIter != appTags.end();
                             ++appTagIter)
                        {
                            const auto& appTag = *appTagIter;

                            const bool appTagToYelpCategoryMappingExists = appTagToYelpCategoriesJsonObj.HasMember(appTag.c_str());
                            if (!appTagToYelpCategoryMappingExists)
                            {
                                continue;
                            }

                            const auto& yelpCategories = appTagToYelpCategoriesJsonObj[appTag.c_str()];

                            if (!yelpCategories.IsArray())
                            {
                                continue;
                            }

                            for (rapidjson::Value::ConstValueIterator yelpCategoriesIter = yelpCategories.Begin();
                                 yelpCategoriesIter != yelpCategories.End();
                                 ++yelpCategoriesIter)
                            {
                                Eegeo_ASSERT(yelpCategoriesIter->IsString());
                                const char* yelpCategory = yelpCategoriesIter->GetString();

                                /*
                                TODO tags: this assert trips -- our mapping data is mapping yelp categories multiple times
                                e.g., culturalcenter appears in both 'art_museums' and 'entertainment'.

                                Eegeo_ASSERT(
                                        out_yelpFoundationCategoryToAppTag.find(yelpCategory) == out_yelpFoundationCategoryToAppTag.end(),
                                        "yelp category %s already exists in map", yelpCategory);
                                */

                                out_yelpFoundationCategoryToAppTag.insert(std::make_pair(yelpCategory, appTag));
                            }
                        }
                    }

                    void ParseYelpAppTagToYelpCategoryMap(
                            const rapidjson::Document& document,
                            std::map<std::string, std::string>& out_appTagToYelpCategory)
                    {
                        const char* appTagToYelpRootCategoriesKey = "app_tag_to_yelp_root_category";

                        Eegeo_ASSERT(document.HasMember(appTagToYelpRootCategoriesKey),
                                "Key doesn't exist: %s\n", appTagToYelpRootCategoriesKey)

                        const auto& appTagToYelpRootCategories = document[appTagToYelpRootCategoriesKey];

                        for (auto appTagIter = appTagToYelpRootCategories.MemberBegin();
                             appTagIter != appTagToYelpRootCategories.MemberEnd();
                             ++appTagIter)
                        {
                            Eegeo_ASSERT(appTagIter->name.IsString());
                            const auto& appTag = appTagIter->name.GetString();

                            Eegeo_ASSERT(appTagIter->value.IsString());
                            const auto& yelpCategory = appTagIter->value.GetString();

                            Eegeo_ASSERT(
                                    out_appTagToYelpCategory.find(appTag) == out_appTagToYelpCategory.end(),
                                    "app tag %s already exists in map", appTag);
                            out_appTagToYelpCategory[appTag] = yelpCategory;
                        }
                    }
                }

                // it basically gets the fine-grained yelp category ("roller disco") and maps it to a known eegeo tag type ("entertainment")
                // we use this when we get a yelp search result back, so we can map it to the appropriate app tag.
                YelpCategoryMappingData ParseYelpData(
                        Eegeo::Helpers::IFileIO& fileIO,
                        const std::vector<std::string>& appTags,
                        const std::string& fileName)
                {
                    const std::string& contents = Helpers::FileHelpers::GetFileContentsAsString(fileIO, fileName);
                    rapidjson::Document document;

                    YelpCategoryMappingData yelpData;
                    if (document.Parse<0>(contents.c_str()).HasParseError())
                    {
                        Eegeo_TTY("Warning: Cannot parse Yelp file: %s!", fileName.c_str());
                        return yelpData;
                    }

                    ParseYelpFoundationCategoryToApplicationTagMap(
                            document, appTags, yelpData.yelpFoundationCategoryToAppTag);

                    ParseYelpAppTagToYelpCategoryMap(document, yelpData.appTagToYelpCategory);

                    const char* defaultAppTagKey = "default_app_tag";

                    Eegeo_ASSERT(document.HasMember(defaultAppTagKey),
                            "cannot find default category: %s", defaultAppTagKey);

                    Eegeo_ASSERT(document[defaultAppTagKey].IsString(), "default category is not a string");

                    yelpData.defaultAppTag = document[defaultAppTagKey].GetString();

                    return yelpData;
                }
            }
        }
    }
}
