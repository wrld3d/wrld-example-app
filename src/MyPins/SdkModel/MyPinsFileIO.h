// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "IFileIO.h"
#include "PersistentSettings.h"
#include "Types.h"
#include "Space.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsFileIO
            {
            public:
                MyPinsFileIO(Eegeo::Helpers::IFileIO& fileIO,
                             PersistentSettings::IPersistentSettingsModel& persistentSetting,
                             IMyPinBoundObjectFactory& myPinBoundObjectFactory,
                             IMyPinBoundObjectRepository& myPinBoundObjectRepository);

                bool TryCacheImageToDisk(Byte* imageData,
                                         size_t imageSize,
                                         int myPinId,
                                         std::string& out_filename);

                void DeleteImageFromDisk(const std::string& imagePath);

                void SavePinModelToDisk(const MyPinModel& pinModel);

                void LoadPinModelsFromDisk(std::vector<std::pair<MyPinModel*, IMyPinBoundObject*> >& out_pinModelBindings, IMyPinsService& myPinsService);

                void SaveAllRepositoryPinsToDisk(const std::vector<MyPinModel*>& pinModels);

                int GetLastIdWrittenToDisk() const;

            private:

                bool WriteJsonToDisk(const std::string& jsonString);

                Eegeo::Helpers::IFileIO& m_fileIO;
                IMyPinBoundObjectFactory& m_myPinBoundObjectFactory;
                IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;

                int m_maxPinId;
            };
        }
    }
}
