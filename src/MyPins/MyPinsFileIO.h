// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IFileIO.h"
#include "PersistentSettings.h"
#include "Types.h"
#include "Space.h"
#include "MyPins.h"

#include <vector>

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsFileIO
        {
        public:
            MyPinsFileIO(Eegeo::Helpers::IFileIO& fileIO,
                         PersistentSettings::IPersistentSettingsModel& persistentSettings);
            
            bool TryCacheImageToDisk(Byte* imageData,
                                     size_t imageSize,
                                     int myPinId,
                                     std::string& out_filename);
            
            void DeleteImageFromDisk(const std::string& imagePath);
            
            void SavePinModelToDisk(const MyPinModel& pinModel);
            
            void LoadPinModelsFromDisk(std::vector<MyPinModel*>& out_pinModels);
            
            void SaveAllRepositoryPinsToDisk(const std::vector<MyPinModel*>& pinModels);
        
            int GetLastIdWrittenToDisk() const;
            
        private:
            
            bool WriteJsonToDisk(const std::string& jsonString);
            
            Eegeo::Helpers::IFileIO& m_fileIO;
            PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
        };
    }
}