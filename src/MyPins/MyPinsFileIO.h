// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IFileIO.h"
#include "PersistentSettings.h"
#include "Types.h"
#include "Space.h"

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
            
            void SavePinModelToDisk(const int pinId,
                                    const std::string& title,
                                    const std::string& description,
                                    const std::string& imagePath,
                                    const Eegeo::Space::LatLong& latLong);
            
        
            int GetLastIdWrittenToDisk() const;
            
        private:
            
            bool WriteJsonToDisk(const std::string& jsonString);
            
            Eegeo::Helpers::IFileIO& m_fileIO;
            PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
        };
    }
}