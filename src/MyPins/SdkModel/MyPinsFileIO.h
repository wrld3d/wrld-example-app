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
            class MyPinsFileIO : private Eegeo::NonCopyable
            {
            public:
                MyPinsFileIO(const std::shared_ptr<Eegeo::Helpers::IFileIO>& fileIO,
                             const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSetting,
                             const std::shared_ptr<IMyPinBoundObjectFactory>& myPinBoundObjectFactory,
                             const std::shared_ptr<IMyPinBoundObjectRepository>& myPinBoundObjectRepository);

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

                const std::shared_ptr<Eegeo::Helpers::IFileIO> m_fileIO;
                const std::shared_ptr<PersistentSettings::IPersistentSettingsModel> m_persistentSettings;
                const std::shared_ptr<IMyPinBoundObjectFactory> m_myPinBoundObjectFactory;
                const std::shared_ptr<IMyPinBoundObjectRepository> m_myPinBoundObjectRepository;
            };
        }
    }
}
