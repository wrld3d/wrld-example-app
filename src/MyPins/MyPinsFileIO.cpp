// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsFileIO.h"
#include "LatLongAltitude.h"
#include "IPersistentSettingsModel.h"
#include "MyPinModel.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

#include <sstream>
#include <vector>


namespace ExampleApp
{
    namespace MyPins
    {
        const std::string MyPinsDataFilename = "pin_data.json";
        const std::string MyPinImagePrefix = "my_pin_image_";
        const std::string MyPins_LastMyPinModelIdKey = "MyPins_LastMyPinModelIdKey";
        const std::string MyPinsJsonArrayName = "myPins";
        
        void CreateEmptyJsonFile(Eegeo::Helpers::IFileIO& fileIO)
        {
            rapidjson::Document jsonDoc;
            jsonDoc.SetObject();
            
            rapidjson::Value myArray(rapidjson::kArrayType);
            
            jsonDoc.AddMember(MyPinsJsonArrayName.c_str(), myArray, jsonDoc.GetAllocator());
            rapidjson::StringBuffer strbuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
            jsonDoc.Accept(writer);
            
            std::string jsonString(strbuf.GetString());
            fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), MyPinsDataFilename);
        }
        
        MyPinsFileIO::MyPinsFileIO(Eegeo::Helpers::IFileIO& fileIO,
                                   PersistentSettings::IPersistentSettingsModel& persistentSettings)
        : m_fileIO(fileIO)
        , m_persistentSettings(persistentSettings)
        {
            if (!m_fileIO.Exists(MyPinsDataFilename))
            {
                CreateEmptyJsonFile(m_fileIO);
            }
            
            int lastId = 0;
            if (!m_persistentSettings.TryGetValue(MyPins_LastMyPinModelIdKey, lastId))
            {
                m_persistentSettings.SetValue(MyPins_LastMyPinModelIdKey, lastId);
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
            
            if (m_fileIO.WriteFile(imageData, imageSize, imagePath))
            {
                out_filename = imagePath;
                return true;
            }
            
            Eegeo_TTY("Couldn't write %s to file\n", imagePath.c_str());
            
            return false;
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
                
                const Eegeo::Space::LatLong& latLong = pinModel.GetLatLong();
                
                rapidjson::Value valueObject(rapidjson::kObjectType);
                valueObject.AddMember("id", pinModel.Identifier(), allocator);
                valueObject.AddMember("title", pinModel.GetTitle().c_str(), allocator);
                valueObject.AddMember("description", pinModel.GetDescription().c_str(), allocator);
                valueObject.AddMember("image", pinModel.GetImagePath().c_str(), allocator);
                valueObject.AddMember("latitude", latLong.GetLatitudeInDegrees(), allocator);
                valueObject.AddMember("longitude", latLong.GetLongitudeInDegrees(), allocator);
            
                myPinsArray.PushBack(valueObject, allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                jsonDoc.Accept(writer);
                std::string jsonString = strbuf.GetString();
                
                if (WriteJsonToDisk(jsonString))
                {
                    m_persistentSettings.SetValue(MyPins_LastMyPinModelIdKey, pinModel.Identifier());
                }
            }
            else
            {
                Eegeo_TTY("Couldn't open file:%s\n", MyPinsDataFilename.c_str());
            }
        }
        
        void MyPinsFileIO::LoadPinModelsFromDisk(std::vector<MyPinModel>& out_pinModels)
        {
            out_pinModels.clear();
            
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
                
                for(int i = 0; i < numEntries; ++i)
                {
                    const rapidjson::Value& entry = myPinsArray[i];
                    
                    int pinId = entry["id"].GetInt();
                    std::string title = entry["title"].GetString();
                    std::string description = entry["description"].GetString();
                    std::string image = entry["image"].GetString();
                    double latitude = entry["latitude"].GetDouble();
                    double longitude = entry["longitude"].GetDouble();
                    
                    out_pinModels.push_back(MyPinModel(pinId,
                                                       title,
                                                       description,
                                                       image,
                                                       Eegeo::Space::LatLong::FromDegrees(latitude, longitude)));
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
            int lastId = -1;
            m_persistentSettings.TryGetValue(MyPins_LastMyPinModelIdKey, lastId);
        
            return lastId;
        }
    }
}