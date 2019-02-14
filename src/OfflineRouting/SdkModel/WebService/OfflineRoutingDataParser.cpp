// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#include "OfflineRoutingDataParser.h"
#include "OfflineRoutingIndoorVersion.h"
#include "document.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                namespace
                {
                    bool TryParseString(const rapidjson::Value& json, const std::string& name, std::string& out_string)
                    {
                        if(json.HasMember(name.c_str()) && json[name.c_str()].IsString())
                        {
                            out_string = json[name.c_str()].GetString();
                            return true;
                        }

                        return false;
                    }

                    bool TryParseVersionFromJsonObject(const rapidjson::Value& json, OfflineRoutingIndoorVersion& out_version)
                    {
                        const std::string buildIdName = "build_id";
                        const std::string submissionCommentName = "submission_comment";
                        const std::string createdAtName = "created_at";
                        const std::string buildStatusName = "build_status";
                        const std::string webManifestUrlName = "web_manifest_url";
                        const std::string mobileManifestUrlName = "mobile_manifest_url";

                        std::string buildId;
                        std::string submissionComment;
                        std::string createdAt;
                        std::string buildStatus;
                        std::string webManifestUrl;
                        std::string mobileManifestUrl;

                        if (!TryParseString(json, buildIdName, buildId))
                        {
                            return false;
                        }

                        if (!TryParseString(json, submissionCommentName, submissionComment))
                        {
                            return false;
                        }

                        if (!TryParseString(json, createdAtName, createdAt))
                        {
                            return false;
                        }

                        if (!TryParseString(json, buildStatusName, buildStatus))
                        {
                            return false;
                        }

                        if (!TryParseString(json, webManifestUrlName, webManifestUrl))
                        {
                            return false;
                        }

                        if (!TryParseString(json, mobileManifestUrlName, mobileManifestUrl))
                        {
                            return false;
                        }

                        out_version.buildId = buildId;
                        out_version.submissionComment = submissionComment;
                        out_version.createdAt = createdAt;
                        out_version.buildStatus = buildStatus;
                        out_version.webManifestUrl = webManifestUrl;
                        out_version.mobileManifestUrl = mobileManifestUrl;

                        return true;
                    }
                }

                OfflineRoutingDataParser::OfflineRoutingDataParser()
                {

                }

                bool OfflineRoutingDataParser::TryParseVersions(const std::string& jsonString,
                                                                std::vector<OfflineRoutingIndoorVersion>& out_versions)
                {
                    rapidjson::Document document;

                    if (!document.Parse<0>(jsonString.c_str()).HasParseError())
                    {
                        size_t numEntries = document.Size();

                        for(int i = 0; i < numEntries; ++i)
                        {
                            const rapidjson::Value& json = document[i];
                            OfflineRoutingIndoorVersion version;

                            if (TryParseVersionFromJsonObject(json, version))
                            {
                                out_versions.push_back(version);
                            }
                            else
                            {
                                return false;
                            }
                        }

                        return true;
                    }

                    return false;
                }
            }
        }
    }
}
