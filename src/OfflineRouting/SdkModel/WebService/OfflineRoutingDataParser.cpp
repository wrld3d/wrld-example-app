// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataParser.h"
#include "StringHelpers.h"
#include "LatLongAltitude.h"
#include "OfflineRoutingFloorData.h"
#include "OfflineRoutingFloorPathData.h"
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
                    const std::string IdKey = "id";
                    const std::string TypeKey = "type";
                    const std::string NameKey = "name";
                    const std::string LevelsKey = "levels";
                    const std::string CoordinatesKey = "coordinates";
                    const std::string PropertiesKey = "properties";
                    const std::string GeometryKey = "geometry";

                    const std::string BuildIdKey = "build_id";
                    const std::string SubmissionCommentKey = "submission_comment";
                    const std::string CreatedAtKey = "created_at";
                    const std::string BuildStatusKey = "build_status";
                    const std::string WebManifestUrlKey = "web_manifest_url";
                    const std::string MobileManifestUrlKey = "mobile_manifest_url";

                    const std::string FloorDataKey = "floor_data";
                    const std::string InterFloorDataKey = "inter_floor_data";
                    const std::string FloorIdKey = "floor_id";
                    const std::string FloorPathsKey = "floor_paths";

                    bool TryParseString(const rapidjson::Value& json, const std::string& name, std::string& out_string)
                    {
                        if(json.HasMember(name.c_str()) && json[name.c_str()].IsString())
                        {
                            out_string = json[name.c_str()].GetString();
                            return true;
                        }

                        return false;
                    }

                    bool TryParseInt(const rapidjson::Value& json, int& out_integer)
                    {
                        if(json.IsInt())
                        {
                            out_integer = json.GetInt();
                            return true;
                        }
                        else if(json.IsString())
                        {
                            return Eegeo::Helpers::TryParseInt(json.GetString(), out_integer);
                        }

                        return false;
                    }

                    bool TryParseIntWithKey(const rapidjson::Value& json, const std::string& key, int& out_integer)
                    {
                        if(json.HasMember(key.c_str()))
                        {
                            return TryParseInt(json[key.c_str()], out_integer);
                        }

                        return false;
                    }

                    bool TryParseDouble(const rapidjson::Value& json, double& out_double)
                    {
                        if(json.IsNumber())
                        {
                            out_double = json.GetDouble();
                            return true;
                        }
                        else if(json.IsString())
                        {
                            return Eegeo::Helpers::TryParseDouble(json.GetString(), out_double);
                        }

                        return false;
                    }

                    template <class T>
                    bool TryParseObjectArray(const rapidjson::Value& document,
                                             std::function<bool(const rapidjson::Value& json, T& out_object)> parseFunction,
                                             std::vector<T>& out_objects)
                    {
                        if (!document.IsArray())
                        {
                            return false;
                        }

                        size_t numEntries = document.Size();

                        for(int i = 0; i < numEntries; ++i)
                        {
                            const rapidjson::Value& json = document[i];
                            T parsedObject;

                            if (parseFunction(json, parsedObject))
                            {
                                out_objects.push_back(parsedObject);
                            }
                            else
                            {
                                return false;
                            }
                        }

                        return true;
                    }

                    template <class T>
                    bool TryParseObjectArray(const rapidjson::Value& document,
                                             const std::string& objectKey,
                                             std::function<bool(const rapidjson::Value& json, T& out_object)> parseFunction,
                                             std::vector<T>& out_objects)
                    {
                        if (document.HasMember(objectKey.c_str()) && document[objectKey.c_str()].IsArray())
                        {
                            return TryParseObjectArray<T>(document[objectKey.c_str()], parseFunction, out_objects);
                        }

                        return false;
                    }

                    bool TryParseDoubleArray(const rapidjson::Value& json, std::vector<double>& out_doubleArray)
                    {
                        return TryParseObjectArray<double>(json, TryParseDouble, out_doubleArray);
                    }

                    bool TryParseCoordinates(const rapidjson::Value& json, std::vector<Eegeo::Space::LatLong>& out_coordinates)
                    {
                        std::vector<std::vector<double>> coordinateValues;
                        if (!TryParseObjectArray<std::vector<double>>(json, CoordinatesKey, TryParseDoubleArray, coordinateValues))
                        {
                            return false;
                        }

                        for(auto const& value: coordinateValues)
                        {
                            if (value.size() < 2)
                            {
                                return false;
                            }

                            double longitude = value.at(0);
                            double latitude = value.at(1);
                            out_coordinates.push_back(Eegeo::Space::LatLong::FromDegrees(latitude, longitude));
                        }

                        return true;
                    }

                    bool TryParseVersionFromJsonObject(const rapidjson::Value& json, OfflineRoutingIndoorVersion& out_version)
                    {
                        std::string buildId;
                        std::string submissionComment;
                        std::string createdAt;
                        std::string buildStatus;
                        std::string webManifestUrl;
                        std::string mobileManifestUrl;

                        if (!TryParseString(json, BuildIdKey, buildId))
                        {
                            return false;
                        }

                        if (!TryParseString(json, SubmissionCommentKey, submissionComment))
                        {
                            return false;
                        }

                        if (!TryParseString(json, CreatedAtKey, createdAt))
                        {
                            return false;
                        }

                        if (!TryParseString(json, BuildStatusKey, buildStatus))
                        {
                            return false;
                        }

                        if (!TryParseString(json, WebManifestUrlKey, webManifestUrl))
                        {
                            return false;
                        }

                        if (!TryParseString(json, MobileManifestUrlKey, mobileManifestUrl))
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

                    bool TryParseFloorPathDataFromJsonObject(const rapidjson::Value& json, OfflineRoutingFloorPathData& out_floorData)
                    {
                        int id = 0;
                        std::string type;
                        std::string name;
                        bool isMultiFloor = false;
                        std::vector<int> levels;
                        std::vector<Eegeo::Space::LatLong> coordinates;

                        if (!json.HasMember(PropertiesKey.c_str()))
                        {
                            return false;
                        }

                        const rapidjson::Value& propertiesJson = json[PropertiesKey.c_str()];

                        if (!json.HasMember(GeometryKey.c_str()))
                        {
                            return false;
                        }

                        const rapidjson::Value& geometryJson = json[GeometryKey.c_str()];

                        if (!TryParseIntWithKey(propertiesJson, IdKey, id))
                        {
                            return false;
                        }

                        if (!TryParseString(propertiesJson, TypeKey, type))
                        {
                            return false;
                        }

                        if (!TryParseString(propertiesJson, NameKey, name))
                        {
                            return false;
                        }

                        if (!TryParseCoordinates(geometryJson, coordinates))
                        {
                            return false;
                        }

                        if (json.HasMember(LevelsKey.c_str()))
                        {
                            isMultiFloor = true;

                            if (!TryParseObjectArray<int>(json, LevelsKey, TryParseInt, levels))
                            {
                                return false;
                            }
                        }

                        out_floorData.id = id;
                        out_floorData.type = type;
                        out_floorData.name = name;
                        out_floorData.isMultiFloor = isMultiFloor;
                        out_floorData.levels = levels;
                        out_floorData.coordinates = coordinates;

                        return true;
                    }

                    bool TryParseFloorDataFromJsonObject(const rapidjson::Value& json, OfflineRoutingFloorData& out_floorData)
                    {
                        int floorId;
                        std::vector<OfflineRoutingFloorPathData> floorPaths;

                        if (!TryParseIntWithKey(json, FloorIdKey, floorId))
                        {
                            return false;
                        }

                        if (!TryParseObjectArray<OfflineRoutingFloorPathData>(json, FloorPathsKey, TryParseFloorPathDataFromJsonObject, floorPaths))
                        {
                            return false;
                        }

                        out_floorData.floorId = floorId;
                        out_floorData.floorPaths = floorPaths;
                        return true;
                    }
                }

                bool OfflineRoutingDataParser::TryParseVersions(const std::string& jsonString,
                                                                std::vector<OfflineRoutingIndoorVersion>& out_versions)
                {
                    rapidjson::Document document;
                    if (!document.Parse<0>(jsonString.c_str()).HasParseError())
                    {
                        return TryParseObjectArray<OfflineRoutingIndoorVersion>(document,
                                                                                TryParseVersionFromJsonObject,
                                                                                out_versions);
                    }

                    return false;
                }

                bool OfflineRoutingDataParser::TryParseFloorData(const std::string& jsonString,
                                                                 std::vector<OfflineRoutingFloorData>& out_floorData)
                {
                    rapidjson::Document document;
                    if (!document.Parse<0>(jsonString.c_str()).HasParseError())
                    {
                        return TryParseObjectArray<OfflineRoutingFloorData>(document,
                                                                            FloorDataKey,
                                                                            TryParseFloorDataFromJsonObject,
                                                                            out_floorData);
                    }

                    return false;
                }

                bool OfflineRoutingDataParser::TryParseMultiFloorData(const std::string& jsonString,
                                                                      std::vector<OfflineRoutingFloorPathData>& out_multiFloorData)
                {
                    rapidjson::Document document;
                    if (!document.Parse<0>(jsonString.c_str()).HasParseError())
                    {
                        return TryParseObjectArray<OfflineRoutingFloorPathData>(document,
                                                                                InterFloorDataKey,
                                                                                TryParseFloorPathDataFromJsonObject,
                                                                                out_multiFloorData);
                    }

                    return false;
                }
            }
        }
    }
}
