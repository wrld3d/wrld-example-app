// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsFileIO.h"
#include "LatLongAltitude.h"

#include <sstream>
#include <vector>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace MyPins
    {
        const std::string MyPinsDataFilename = "pin_data.json";
        const std::string MyPinImagePrefix = "my_pin_image_";
        const std::string MyPinsJsonArrayName = "myPins";
        
        void CreateEmptyJsonFile(Eegeo::Helpers::IFileIO& fileIO)
        {
            rapidjson::Document jsonDoc;
            jsonDoc.SetObject();
            rapidjson::Value myArray(rapidjson::kArrayType);
            rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
            
            jsonDoc.AddMember(MyPinsJsonArrayName.c_str(), myArray, allocator);
            rapidjson::StringBuffer strbuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
            jsonDoc.Accept(writer);
            
            std::string jsonString(strbuf.GetString());
            fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), MyPinsDataFilename);
        }
        
        template<typename T>
        std::string ConvertModelDetailToString(const T& detail)
        {
            std::stringstream ss;
            ss << detail;
            return ss.str();
        }
        
        MyPinsFileIO::MyPinsFileIO(Eegeo::Helpers::IFileIO& fileIO)
        : m_fileIO(fileIO)
        {
            if (!m_fileIO.Exists(MyPinsDataFilename))
            {
                CreateEmptyJsonFile(m_fileIO);
            }
        }
        
        bool MyPinsFileIO::TryCacheImageToDisk(Byte* imageData,
                                               size_t imageSize,
                                               unsigned int myPinId,
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
        
        void MyPinsFileIO::SavePinModelToDisk(const unsigned int pinId,
                                              const std::string& title,
                                              const std::string& description,
                                              const std::string& imagePath,
                                              const Eegeo::Space::LatLong& latLong)
        {
            std::fstream stream;
            size_t size;
            
            if (m_fileIO.OpenFile(stream, size, MyPinsDataFilename))
            {
                std::vector<Byte> readData;
                readData.resize(size);
                stream.read((char*)&readData[0], size);
                unsigned char* buffer = &readData[0];

                rapidjson::Document jsonDoc;
                jsonDoc.Parse<0>((const char*)buffer);

                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value& myPinsArray = jsonDoc[MyPinsJsonArrayName.c_str()];
                
                std::string idAsString = ConvertModelDetailToString(pinId);
                std::string latitudeString = ConvertModelDetailToString(latLong.GetLatitudeInDegrees());
                std::string longitudeString = ConvertModelDetailToString(latLong.GetLongitudeInDegrees());
                
                rapidjson::Value valueObject(rapidjson::kObjectType);
                valueObject.AddMember("id", idAsString.c_str(), allocator);
                valueObject.AddMember("title", title.c_str(), allocator);
                valueObject.AddMember("description", description.c_str(), allocator);
                valueObject.AddMember("image", imagePath.c_str(), allocator);
                valueObject.AddMember("latitude", latitudeString.c_str(), allocator);
                valueObject.AddMember("longitude", longitudeString.c_str(), allocator);
            
                myPinsArray.PushBack(valueObject, allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                jsonDoc.Accept(writer);
                std::string jsonString = strbuf.GetString();
                WriteJsonToDisk(jsonString);
            }
        }
        
        bool MyPinsFileIO::WriteJsonToDisk(const std::string &jsonString)
        {
            m_fileIO.DeleteFile(MyPinsDataFilename);
            return m_fileIO.WriteFile((Byte*)jsonString.c_str(), jsonString.size(), MyPinsDataFilename);
        }
    }
}