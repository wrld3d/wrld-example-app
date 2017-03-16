// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <algorithm>
#include <sstream>
#include <vector>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "InteriorId.h"
#include "MyPinsFileIO.h"
#include "LatLongAltitude.h"
#include "IPersistentSettingsModel.h"
#include "MyPinModel.h"
#include "IMyPinBoundObject.h"
#include "MyPinsSemanticPinType.h"
#include "IMyPinBoundObjectFactory.h"
#include "IMyPinBoundObjectRepository.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            namespace Legacy
            {
                const int legacyIconCount = 25;
                const std::string iconIndexToKey[legacyIconCount] = {
                    "tourism",    // 0
                    "food_drink",
                    "food_drink",
                    "entertainment",
                    "sports_leisure",
                    
                    "entertainment",    // 5
                    "accommodation",
                    "art_museums",
                    "art_museums",
                    "my_pins",
                    
                    "tour_entry",    //10
                    "indoor_map_entry",
                    "default",             // (guidekick)
                    "feed_twitter",
                    "feed_youtube",
                    
                    "default",    //15   (instagram)
                    "feed_facebook",
                    "feed_weblink",
                    "feed_wikipedia",
                    "default",      // (blank icon)
                    
                    "feed_vimeo",    // 20
                    "feed_google_plus",
                    "feed_picasa",
                    "default",      // (blank icon)
                    "default"       // (blank icon)
                };
                
                std::string PinIconKeyFromLegacyIconIndex(const rapidjson::Value& entry)
                {
                    if (entry.HasMember("icon"))
                    {
                        const int legacyIconIndex = entry["icon"].GetInt();
                        
                        if (legacyIconIndex >= 0 && legacyIconIndex < legacyIconCount)
                        {
                            return iconIndexToKey[legacyIconIndex];
                        }
                        else
                        {
                            return "default";
                        }
                    }
                    else
                    {
                        return "my_pins";
                    }
                }
                
            }
            
            namespace
            {
                void MyPinModelToJson(const MyPinModel& pinModel, rapidjson::Document::AllocatorType& allocator, IMyPinBoundObjectRepository& myPinBoundObjectRepository, rapidjson::Value& out_value)
                {
                    const Eegeo::Space::LatLong& latLong = pinModel.GetLatLong();
                    
                    rapidjson::Value valueObject(rapidjson::kObjectType);
                    valueObject.AddMember("version", pinModel.Version(), allocator);
                    valueObject.AddMember("id", pinModel.Identifier(), allocator);
                    valueObject.AddMember("title", rapidjson::Value(pinModel.GetTitle().c_str(), allocator).Move(), allocator);
                    valueObject.AddMember("description", rapidjson::Value(pinModel.GetDescription().c_str(), allocator).Move(), allocator);
                    valueObject.AddMember("vendor", rapidjson::Value(pinModel.GetVendor().c_str(), allocator).Move(), allocator);
                    valueObject.AddMember("ratingsImage", rapidjson::Value(pinModel.GetRatingsImage().c_str(), allocator).Move(), allocator);
                    valueObject.AddMember("reviewCount", pinModel.GetReviewsCount(), allocator);
                    valueObject.AddMember("pinIconKey", rapidjson::Value(pinModel.GetPinIconKey().c_str(), allocator).Move(), allocator);
                    valueObject.AddMember("latitude", latLong.GetLatitudeInDegrees(), allocator);
                    valueObject.AddMember("longitude", latLong.GetLongitudeInDegrees(), allocator);
                    valueObject.AddMember("heightAboveTerrain", pinModel.GetHeightAboveTerrainMetres(), allocator);
                    valueObject.AddMember("interior", pinModel.IsInterior(), allocator);
                    valueObject.AddMember("building", rapidjson::Value(pinModel.GetBuildingId().Value().c_str(), allocator).Move(), allocator);
                    valueObject.AddMember("floor", pinModel.GetFloor(), allocator);
                    
                    IMyPinBoundObject& pinBoundObject(myPinBoundObjectRepository.GetBoundObjectForPin(pinModel));
                    valueObject.AddMember("type", static_cast<int>(pinBoundObject.GetSemanticPinType()), allocator);
                    valueObject.AddMember("metadata", rapidjson::Value(pinBoundObject.GetSerialized().c_str(), allocator).Move(), allocator);
                    
                    out_value = valueObject;
                }
                
                std::string ParsePinIconKey(const rapidjson::Value& entry)
                {
                    const int version = entry["version"].GetInt();
                    
                    const int earliestVersionWithPinIconKey = 4;
                    if (version >= earliestVersionWithPinIconKey)
                    {
                        return entry["pinIconKey"].GetString();
                    }
                    else
                    {
                        return Legacy::PinIconKeyFromLegacyIconIndex(entry);
                    }
                }

                int FindMaxId(const rapidjson::Value& myPinsArray)
                {
                    int maxId = 0;
                    for (rapidjson::SizeType i = 0; i < myPinsArray.Size(); ++i)
                    {
                        if (myPinsArray[i].HasMember("id"))
                        {
                            maxId = std::max<int>(maxId, myPinsArray[i]["id"].GetInt());
                        }
                    }

                    return maxId;
                }
            }
            
            const std::string MyPinsDataFilename = "pin_data.json";
            const std::string MyPinImagePrefix = "my_pin_image_";
            const std::string MyPinsJsonArrayName = "myPins";

            void CreateEmptyJsonFile(Eegeo::Helpers::IFileIO& fileIO)
            {
                rapidjson::Document jsonDoc;
                jsonDoc.SetObject();

                rapidjson::Value myArray(rapidjson::kArrayType);

                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                jsonDoc.AddMember(rapidjson::Value(MyPinsJsonArrayName.c_str(), allocator).Move(), myArray, allocator);
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                jsonDoc.Accept(writer);

                std::string jsonString(strbuf.GetString());
                fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), MyPinsDataFilename);
            }

            MyPinsFileIO::MyPinsFileIO(Eegeo::Helpers::IFileIO& fileIO,
                                       PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                       IMyPinBoundObjectFactory& myPinBoundObjectFactory,
                                       IMyPinBoundObjectRepository& myPinBoundObjectRepository)
                : m_fileIO(fileIO)
                , m_myPinBoundObjectFactory(myPinBoundObjectFactory)
                , m_myPinBoundObjectRepository(myPinBoundObjectRepository)
            , m_maxPinId(0)
            {
                if (!m_fileIO.Exists(MyPinsDataFilename))
                {
                    CreateEmptyJsonFile(m_fileIO);
                }
            }

            bool MyPinsFileIO::TryCacheImageToDisk(Byte* imageData,
                                                   size_t imageSize,
                                                   int myPinId,
                                                   std::string& out_filename)
            {
                out_filename = "";

                std::stringstream ss;
                ss << MyPinImagePrefix << myPinId << ".jpg";

                std::string imagePath = ss.str();

                if (m_fileIO.Exists(imagePath))
                {
                    Eegeo_TTY("%s already exists\n", imagePath.c_str());
                    return false;
                }

                if (m_fileIO.WriteFile(imageData, imageSize, imagePath, std::fstream::out | std::fstream::binary))
                {
                    out_filename = imagePath;
                    return true;
                }

                Eegeo_TTY("Couldn't write %s to file\n", imagePath.c_str());

                return false;
            }

            void MyPinsFileIO::DeleteImageFromDisk(const std::string& imagePath)
            {
                if (m_fileIO.Exists(imagePath))
                {
                    m_fileIO.DeleteFile(imagePath);
                }
            }

            void MyPinsFileIO::SavePinModelToDisk(const MyPinModel& pinModel)
            {
                std::fstream stream;
                size_t size;

                if (m_fileIO.OpenFile(stream, size, MyPinsDataFilename))
                {
                    std::string json((std::istreambuf_iterator<char>(stream)),
                                     (std::istreambuf_iterator<char>()));

                    rapidjson::Document jsonDoc;
                    if (jsonDoc.Parse<0>(json.c_str()).HasParseError())
                    {
                        Eegeo_TTY("Parse error in MyPins JSON.\n");
                        return;
                    }

                    Eegeo_ASSERT(jsonDoc.IsObject(), "JSON document is not of object type");

                    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                    rapidjson::Value& myPinsArray = jsonDoc[MyPinsJsonArrayName.c_str()];

                    rapidjson::Value pinModelJson;
                    MyPinModelToJson(pinModel, allocator, m_myPinBoundObjectRepository, pinModelJson);
                    m_maxPinId = FindMaxId(myPinsArray);
                    
                    myPinsArray.PushBack(pinModelJson, allocator);

                    rapidjson::StringBuffer strbuf;
                    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                    jsonDoc.Accept(writer);
                    std::string jsonString = strbuf.GetString();

                    WriteJsonToDisk(jsonString);
                }
                else
                {
                    Eegeo_TTY("Couldn't open file:%s\n", MyPinsDataFilename.c_str());
                }
            }

            void MyPinsFileIO::SaveAllRepositoryPinsToDisk(const std::vector<MyPinModel*>& pinModels)
            {
                if (m_fileIO.Exists(MyPinsDataFilename))
                {
                    m_fileIO.DeleteFile(MyPinsDataFilename);
                }

                rapidjson::Document jsonDoc;
                jsonDoc.SetObject();

                rapidjson::Value pinsArray(rapidjson::kArrayType);
                pinsArray.SetArray();
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

                jsonDoc.AddMember(rapidjson::Value(MyPinsJsonArrayName.c_str(), allocator).Move(), pinsArray, allocator);
                rapidjson::Value& myPinsArray = jsonDoc[MyPinsJsonArrayName.c_str()];

                for (std::vector<MyPinModel*>::const_iterator it = pinModels.begin(); it != pinModels.end(); ++it)
                {
                    const MyPinModel* pinModel = *it;

                    rapidjson::Value pinModelJson;
                    MyPinModelToJson(*pinModel, allocator, m_myPinBoundObjectRepository, pinModelJson);

                    myPinsArray.PushBack(pinModelJson, allocator);
                }

                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                jsonDoc.Accept(writer);

                std::string jsonString(strbuf.GetString());
                m_fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), MyPinsDataFilename);
            }

            void MyPinsFileIO::LoadPinModelsFromDisk(std::vector<std::pair<MyPinModel*, IMyPinBoundObject*> >& out_pinModelBindings, IMyPinsService& myPinService)
            {
                out_pinModelBindings.clear();

                std::fstream stream;
                size_t size;

                if (m_fileIO.OpenFile(stream, size, MyPinsDataFilename))
                {
                    std::string json((std::istreambuf_iterator<char>(stream)),
                                     (std::istreambuf_iterator<char>()));

                    rapidjson::Document jsonDoc;
                    if (jsonDoc.Parse<0>(json.c_str()).HasParseError())
                    {
                        Eegeo_TTY("Parse error in MyPins JSON.\n");
                        return;
                    }

                    Eegeo_ASSERT(jsonDoc.IsObject(), "JSON document is not of object type");

                    const rapidjson::Value& myPinsArray = jsonDoc[MyPinsJsonArrayName.c_str()];
                    size_t numEntries = myPinsArray.Size();
                    m_maxPinId = FindMaxId(myPinsArray);

                    for(int i = 0; i < numEntries; ++i)
                    {
                        const rapidjson::Value& entry = myPinsArray[i];
                        
                        Eegeo_ASSERT(entry.HasMember("version"),
                                     "Old MyPinModel version detected. Please delete and reinstall the application.\n");
                        
                        const int version = entry["version"].GetInt();
                        
                        const int earliestSupportedVersion = 1;
                        Eegeo_ASSERT(version >= earliestSupportedVersion, "Old MyPinModel version detected: tried to deserialize version %d but current version is %d. Please delete and reinstall the application.\n", version, MyPinModel::CurrentVersion);
                        
                        
                        
                        MyPinModel::TPinIdType pinId = entry["id"].GetInt();
                        std::string title = entry["title"].GetString();
                        std::string description = entry["description"].GetString();
                        
                        const std::string& pinIconKey = ParsePinIconKey(entry);
                        
                        double latitude = entry["latitude"].GetDouble();
                        double longitude = entry["longitude"].GetDouble();
                        MyPinsSemanticPinType semanticPinType = static_cast<MyPinsSemanticPinType>(entry["type"].GetInt());
                        std::string pinMetadataJson = entry["metadata"].GetString();
                        
                        std::string ratingsImage = "";
                        int reviewCount = 0;
                        
                        if(version == 1)
                        {
                            // MB: Cannot infer review count therefore cannot show ratings by Yelp branding rules.
                            if(description.find("stars_") == 0)
                            {
                                description = "";
                            }
                        }
                        else if(version >= 2)
                        {
                            ratingsImage = entry["ratingsImage"].GetString();
                            reviewCount = entry["reviewCount"].GetInt();
                        }
                        
                        std::string vendor = Search::YelpVendorName;
                        if(version == MyPinModel::CurrentVersion)
                        {
                            vendor = entry["vendor"].GetString();
                        }
                        
                        float heightAboveTerrainMetres = 0;
                        if(entry.HasMember("heightAboveTerrain"))
                        {
                            heightAboveTerrainMetres = static_cast<float>(entry["heightAboveTerrain"].GetDouble());
                        }
                        
                        bool interior = false;
                        if(entry.HasMember("interior"))
                        {
                            interior = entry["interior"].GetBool();
                        }
                        
                        std::string buildingId("");
                        if(entry.HasMember("building"))
                        {
                            buildingId = entry["building"].GetString();
                        }
                        
                        int floor = 0;
                        if(entry.HasMember("floor"))
                        {
                            floor = entry["floor"].GetInt();
                        }
                        
                        IMyPinBoundObject* pPinBoundObject(m_myPinBoundObjectFactory.CreatePinBoundObjectFromSerialized(*this,
                                                                                                                        pinId,
                                                                                                                        semanticPinType,
                                                                                                                        pinMetadataJson,
                                                                                                                        pinIconKey,
                                                                                                                        myPinService));
                        
                        if(pPinBoundObject == NULL)
                        {
                            Eegeo_TTY("Failed to create a pin object for this pin, skipping to the next one");
                            continue;
                        }
                    
                        MyPinModel* pModel(Eegeo_NEW(MyPinModel)(version,
                                                                 pinId,
                                                                 title,
                                                                 description,
                                                                 vendor,
                                                                 ratingsImage,
                                                                 pinIconKey,
                                                                 reviewCount,
                                                                 Eegeo::Space::LatLong::FromDegrees(latitude, longitude),
                                                                 heightAboveTerrainMetres,
                                                                 interior,
                                                                 buildingId,
                                                                 floor));
                        
                        out_pinModelBindings.push_back(std::make_pair(pModel, pPinBoundObject));
                    }
                }
            }
            
            bool MyPinsFileIO::WriteJsonToDisk(const std::string &jsonString)
            {
                m_fileIO.DeleteFile(MyPinsDataFilename);
                return m_fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), MyPinsDataFilename);
            }

            int MyPinsFileIO::GetLastIdWrittenToDisk() const
            {
                return m_maxPinId;
            }
        }
    }
}
