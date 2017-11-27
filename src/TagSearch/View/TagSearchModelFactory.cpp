// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "TagSearchModelFactory.h"
#include "document.h"
#include "Types.h"
#include "FileHelpers.h"
#include "ApiKey.h"
#include "base64.h"
#include "ApplicationConfigurationXorCipher.h"
#include "ApplicationConfigurationBuilder.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace View
        {
            namespace
            {
                const std::string Encrypted = "Encrypted";
                const std::string HMAC_SHA1 = "HMAC_SHA1";

                void ParseJson(const std::string& json, std::vector<ExampleApp::TagSearch::View::TagSearchModel>& out_models, const std::string& jsonAttributeName)
                {
                    rapidjson::Document document;

                    if (document.Parse<0>(json.c_str()).HasParseError())
                    {
                        Eegeo_ASSERT(false, "failed to parse json");
                        return;
                    }

                    if (document.HasMember(Encrypted.c_str()))
                    {
                        Eegeo_ASSERT(document.HasMember(HMAC_SHA1.c_str()), "must have HMAC_SHA1 digest field if Encrypted field is present");

                        const std::string& configKey = base64_decode(ExampleApp::ApplicationConfigurationSecret);
                        ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationXorCipher cipher(configKey);
                        ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationBuilder builder(cipher, configKey);

                        const std::string& encryptedValue = document[Encrypted.c_str()].GetString();
                        const std::string& digest = document[HMAC_SHA1.c_str()].GetString();

                        const std::string& decrypted = builder.Decrypt(encryptedValue);
                        const bool validHMAC = builder.ValidateHMAC(decrypted, digest);
                        Eegeo_ASSERT(validHMAC, "HMAC_SHA1 digest does not match, check that app secret matches that used to encrypt app config");

                        document.Parse<0>(decrypted.c_str());

                        Eegeo_ASSERT(!document.HasParseError(), "unable to parse Encrypted config field");
                    }

                    const char* itemKey = jsonAttributeName.c_str();
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
                                                                                       Eegeo::Helpers::IFileIO& fileIO, const std::string& fileName, const std::string& jsonAttributeName)
            {
                const std::string& json = Helpers::FileHelpers::GetFileContentsAsString(fileIO, fileName);

                std::vector<ExampleApp::TagSearch::View::TagSearchModel> result;
                ParseJson(json, result, jsonAttributeName);
                return result;
            }
        }
    }
}
