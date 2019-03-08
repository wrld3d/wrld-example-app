// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingFileIO.h"
#include "OfflineRoutingFeature.h"
#include "OfflineRoutingGraphNode.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                namespace
                {
                    const static char* FeaturesJsonArrayName = "features";
                    const static char* NodesJsonArrayName = "nodes";

                    const std::string GetFileName(const std::string& buildId)
                    {
                        return buildId + ".json";
                    }

                    void FeatureModelToJson(const OfflineRoutingFeature& feature, rapidjson::Document::AllocatorType& allocator, rapidjson::Value& out_value)
                    {
                        rapidjson::Value valueObject(rapidjson::kObjectType);
                        valueObject.AddMember("id", static_cast<int>(feature.GetId()), allocator);
                        valueObject.AddMember("type", rapidjson::Value(feature.GetType().c_str(), allocator).Move(), allocator);
                        valueObject.AddMember("name", rapidjson::Value(feature.GetName().c_str(), allocator).Move(), allocator);
                        valueObject.AddMember("indoorId", rapidjson::Value(feature.GetInteriorId().Value().c_str(), allocator).Move(), allocator);
                        valueObject.AddMember("isMultiFloor", feature.GetIsMultiFloor(), allocator);
                        valueObject.AddMember("isOneWay", feature.GetIsOneWay(), allocator);
                        valueObject.AddMember("durationMultiplier", feature.GetDurationMultiplier(), allocator);

                        rapidjson::Value nodesArray(rapidjson::kArrayType);
                        nodesArray.SetArray();

                        valueObject.AddMember(rapidjson::Value("featureNodes", allocator).Move(), nodesArray, allocator);
                        rapidjson::Value& featureNodesArray = valueObject["featureNodes"];

                        const auto& featureNodes = feature.GetLinkedNodes();
                        for (const auto &nodeId : featureNodes)
                        {
                            featureNodesArray.PushBack(rapidjson::Value(static_cast<int>(nodeId)), allocator);
                        }

                        rapidjson::Value pointsArray(rapidjson::kArrayType);
                        pointsArray.SetArray();

                        valueObject.AddMember(rapidjson::Value("featureSpline", allocator).Move(), pointsArray, allocator);
                        rapidjson::Value& featureSplineArray = valueObject["featureSpline"];

                        const auto& splinePoints = feature.GetSpline().Points();
                        for (const auto &point : splinePoints)
                        {
                            rapidjson::Value pointObject(rapidjson::kObjectType);
                            pointObject.AddMember("x", point.x, allocator);
                            pointObject.AddMember("y", point.y, allocator);
                            pointObject.AddMember("z", point.z, allocator);
                            featureSplineArray.PushBack(pointObject, allocator);
                        }

                        out_value = valueObject;
                    }

                    void NodeModelToJson(const OfflineRoutingGraphNode& node, rapidjson::Document::AllocatorType& allocator, rapidjson::Value& out_value)
                    {
                        rapidjson::Value valueObject(rapidjson::kObjectType);

                        const auto& point = node.GetPoint();
                        rapidjson::Value pointObject(rapidjson::kObjectType);
                        pointObject.AddMember("x", point.x, allocator);
                        pointObject.AddMember("y", point.y, allocator);
                        pointObject.AddMember("z", point.z, allocator);

                        valueObject.AddMember("point", pointObject, allocator);
                        valueObject.AddMember("id", static_cast<int>(node.GetId()), allocator);
                        valueObject.AddMember("floorId", node.GetFloorId(), allocator);
                        valueObject.AddMember("featureId", static_cast<int>(node.GetFeatureId()), allocator);
                        valueObject.AddMember("indoorId", rapidjson::Value(node.GetInteriorId().Value().c_str(), allocator).Move(), allocator);

                        rapidjson::Value edgesArray(rapidjson::kArrayType);
                        edgesArray.SetArray();

                        valueObject.AddMember(rapidjson::Value("nodeEdges", allocator).Move(), edgesArray, allocator);
                        rapidjson::Value& nodeEdgesArray = valueObject["nodeEdges"];

                        const auto& nodeEdges = node.GetEdges();
                        for (const auto &nodeId : nodeEdges)
                        {
                            nodeEdgesArray.PushBack(rapidjson::Value(static_cast<int>(nodeId)), allocator);
                        }

                        out_value = valueObject;
                    }

                    OfflineRoutingFeature ParseFeature(const rapidjson::Value& feature)
                    {
                        OfflineRoutingFeatureId id = static_cast<OfflineRoutingFeatureId>(feature["id"].GetInt());
                        std::string type = feature["type"].GetString();
                        std::string name = feature["name"].GetString();
                        std::string indoorId = feature["indoorId"].GetString();
                        bool isMultiFloor = feature["isMultiFloor"].GetBool();
                        bool isOneWay = feature["isOneWay"].GetBool();
                        int durationMultiplier = feature["durationMultiplier"].GetInt();

                        const auto& featureNodesJsonArray = feature["featureNodes"];
                        Eegeo_ASSERT(featureNodesJsonArray.IsArray(), "Features nodes is not of array type");
                        size_t featureNodesArraySize = featureNodesJsonArray.Size();
                        std::vector<OfflineRoutingGraphNodeId> featureNodes;
                        featureNodes.reserve(featureNodesArraySize);
                        for(int i = 0; i < featureNodesArraySize; ++i)
                        {
                            int featureNodeId = featureNodesJsonArray[i].GetInt();
                            featureNodes.emplace_back(static_cast<OfflineRoutingGraphNodeId>(featureNodeId));
                        }

                        const auto& featureSplineJsonArray = feature["featureSpline"];
                        Eegeo_ASSERT(featureSplineJsonArray.IsArray(), "Features spline is not of array type");
                        size_t featureSplineArraySize = featureSplineJsonArray.Size();
                        std::vector<Eegeo::v3> featureSpline;
                        featureSpline.reserve(featureSplineArraySize);
                        for(int i = 0; i < featureSplineArraySize; ++i)
                        {
                            const auto& splinePoint = featureSplineJsonArray[i];
                            float x = static_cast<float>(splinePoint["x"].GetDouble());
                            float y = static_cast<float>(splinePoint["y"].GetDouble());
                            float z = static_cast<float>(splinePoint["z"].GetDouble());
                            featureSpline.emplace_back(x, y, z);
                        }

                        return OfflineRoutingFeature(id,
                                                     type,
                                                     name,
                                                     indoorId,
                                                     isMultiFloor,
                                                     featureNodes,
                                                     Eegeo::Geometry::Point3Spline::BuildFromPoints(featureSpline),
                                                     isOneWay,
                                                     durationMultiplier);
                    }

                    std::vector<OfflineRoutingFeature> ParseFeatures(const rapidjson::Value& featuresArray)
                    {
                        Eegeo_ASSERT(featuresArray.IsArray(), "Features json is not of array type");
                        size_t numEntries = featuresArray.Size();
                        std::vector<OfflineRoutingFeature> parsedFeatures;
                        parsedFeatures.reserve(numEntries);

                        for(int i = 0; i < numEntries; ++i)
                        {
                            parsedFeatures.emplace_back(ParseFeature(featuresArray[i]));
                        }

                        return parsedFeatures;
                    }

                    OfflineRoutingGraphNode ParseGraphNode(const rapidjson::Value& graphNode)
                    {
                        OfflineRoutingGraphNodeId id = static_cast<OfflineRoutingGraphNodeId>(graphNode["id"].GetInt());
                        int floorId = graphNode["floorId"].GetInt();
                        OfflineRoutingFeatureId featureId = static_cast<OfflineRoutingFeatureId>(graphNode["featureId"].GetInt());
                        std::string indoorId = graphNode["indoorId"].GetString();

                        const auto& pointJson = graphNode["point"];
                        double x = pointJson["x"].GetDouble();
                        double y = pointJson["y"].GetDouble();
                        double z = pointJson["z"].GetDouble();

                        const auto& nodeEdgesArray = graphNode["nodeEdges"];
                        Eegeo_ASSERT(nodeEdgesArray.IsArray(), "Node edges is not of array type");
                        size_t nodeEdgesArraySize = nodeEdgesArray.Size();
                        std::vector<OfflineRoutingGraphNodeId> nodeEdges;
                        nodeEdges.reserve(nodeEdgesArraySize);
                        for(int i = 0; i < nodeEdgesArraySize; ++i)
                        {
                            int nodeId = nodeEdgesArray[i].GetInt();
                            nodeEdges.emplace_back(static_cast<OfflineRoutingGraphNodeId>(nodeId));
                        }

                        return OfflineRoutingGraphNode(id,
                                                       Eegeo::dv3(x, y, z),
                                                       nodeEdges,
                                                       floorId,
                                                       featureId,
                                                       indoorId);
                    }

                    std::vector<OfflineRoutingGraphNode> ParseGraphNodes(const rapidjson::Value& graphNodesArray)
                    {
                        Eegeo_ASSERT(graphNodesArray.IsArray(), "Graph Nodes json is not of array type");
                        size_t numEntries = graphNodesArray.Size();
                        std::vector<OfflineRoutingGraphNode> parsedGraphNodes;
                        parsedGraphNodes.reserve(numEntries);

                        for(int i = 0; i < numEntries; ++i)
                        {
                            parsedGraphNodes.emplace_back(ParseGraphNode(graphNodesArray[i]));
                        }

                        return parsedGraphNodes;
                    }
                }


                OfflineRoutingFileIO::OfflineRoutingFileIO(Eegeo::Helpers::IFileIO& fileIO)
                : m_fileIO(fileIO)
                {}

                void OfflineRoutingFileIO::SaveGraphToStorage(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                              const OfflineRoutingFeatures& features,
                                                              const OfflineRoutingGraphNodes& graphNodes)
                {
                    const std::string& fileName = GetFileName(interiorId.Value());
                    if (m_fileIO.Exists(fileName))
                    {
                        m_fileIO.DeleteFile(fileName);
                    }

                    rapidjson::Document jsonDoc;
                    jsonDoc.SetObject();
                    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

                    rapidjson::Value featuresArray(rapidjson::kArrayType);
                    featuresArray.SetArray();

                    jsonDoc.AddMember(rapidjson::Value(FeaturesJsonArrayName, allocator).Move(), featuresArray, allocator);
                    rapidjson::Value& graphFeaturesArray = jsonDoc[FeaturesJsonArrayName];

                    for (const auto &featurePair : features)
                    {
                        const auto& featureModel = featurePair.second;

                        rapidjson::Value featureModelJson;
                        FeatureModelToJson(featureModel, allocator, featureModelJson);

                        graphFeaturesArray.PushBack(featureModelJson, allocator);
                    }

                    rapidjson::Value nodesArray(rapidjson::kArrayType);
                    nodesArray.SetArray();

                    jsonDoc.AddMember(rapidjson::Value(NodesJsonArrayName, allocator).Move(), nodesArray, allocator);
                    rapidjson::Value& graphNodesArray = jsonDoc[NodesJsonArrayName];

                    for (const auto &nodePair : graphNodes)
                    {
                        rapidjson::Value nodeModelJson;
                        NodeModelToJson(nodePair.second, allocator, nodeModelJson);
                        graphNodesArray.PushBack(nodeModelJson, allocator);
                    }

                    rapidjson::StringBuffer strbuf;
                    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                    jsonDoc.Accept(writer);

                    std::string jsonString(strbuf.GetString());
                    m_fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), fileName);
                }

                bool OfflineRoutingFileIO::LoadGraphFromStorage(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                std::vector<OfflineRoutingFeature>& out_features,
                                                                std::vector<OfflineRoutingGraphNode>& out_graphNodes)
                {
                    const std::string& fileName = GetFileName(interiorId.Value());

                    if (!m_fileIO.Exists(fileName))
                    {
                        return false;
                    }

                    std::fstream stream;
                    size_t size;

                    if (m_fileIO.OpenFile(stream, size, fileName))
                    {
                        std::string json((std::istreambuf_iterator<char>(stream)),
                                         (std::istreambuf_iterator<char>()));

                        rapidjson::Document jsonDoc;
                        if (jsonDoc.Parse<0>(json.c_str()).HasParseError()) {
                            Eegeo_TTY("Parse error in Offline Nav JSON.\n");
                            return false;
                        }

                        Eegeo_ASSERT(jsonDoc.IsObject(), "JSON document is not of object type");

                        const auto& features = jsonDoc[FeaturesJsonArrayName];
                        const auto& nodes = jsonDoc[NodesJsonArrayName];

                        out_features = ParseFeatures(features);
                        out_graphNodes = ParseGraphNodes(nodes);
                        return true;
                    }

                    return false;
                }
            }
        }
    }
}
