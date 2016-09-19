// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "TagSearchModelFactory.h"
#include "document.h"
#include "Types.h"
#include "FileHelpers.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            namespace
            {
                void ParseJson(const std::string& json, std::vector<ExampleApp::TagSearch::View::TagSearchModel>& out_models)
                {
                    rapidjson::Document document;

                    if (document.Parse<0>(json.c_str()).HasParseError())
                    {
                        Eegeo_ASSERT(false, "failed to parse json");
                        return;
                    }

                    const char* itemKey = "items";
                    Eegeo_ASSERT(document.HasMember(itemKey));

                    const auto& tagSearchModelsMember = document[itemKey];
                    Eegeo_ASSERT(tagSearchModelsMember.IsArray());

                    out_models = std::vector<ExampleApp::TagSearch::View::TagSearchModel>();

                    for (rapidjson::Value::ConstValueIterator it = tagSearchModelsMember.Begin();
                         it != tagSearchModelsMember.End();
                         ++it)
                    {
                        const auto& item = *it;

                        const char* nameKey = "name";
                        Eegeo_ASSERT(item.HasMember(nameKey))
                        Eegeo_ASSERT(item[nameKey].IsString())
                        const std::string& name = item[nameKey].GetString();

                        // search tag
                        const char* searchTagKey = "search_tag";
                        Eegeo_ASSERT(item.HasMember(searchTagKey))
                        Eegeo_ASSERT(item[searchTagKey].IsString());
                        const std::string& searchTag = item[searchTagKey].GetString();

                        // icon
                        const char* iconKey = "icon_key";
                        Eegeo_ASSERT(item.HasMember(iconKey));
                        Eegeo_ASSERT(item[iconKey].IsString());
                        const std::string& icon = item[iconKey].GetString();

                        const bool visibleInSearchMenu = true;
                        const bool interior = true;

                        // TODO: do parsing for extended options, such as is_interior? and radius searching. This needs
                        // looked at in conjunction with other apps.
                        out_models.push_back(TagSearchModel(name, searchTag, interior, icon, visibleInSearchMenu));
                    }
                }
            }

            std::vector<TagSearch::View::TagSearchModel> CreateTagSearchModelsFromFile(
                    Eegeo::Helpers::IFileIO& fileIO, const std::string& fileName)
            {
                const std::string& json = Helpers::FileHelpers::GetFileContentsAsString(fileIO, fileName);

                std::vector<ExampleApp::TagSearch::View::TagSearchModel> result;
                ParseJson(json, result);
                return result;
            }
        }
    }
}
