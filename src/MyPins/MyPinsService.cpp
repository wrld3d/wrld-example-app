// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsService.h"
#include "IMyPinsRepository.h"
#include "PinRepository.h"
#include "IWorldPinsFactory.h"
#include "Pin.h"
#include "MyPinsFileIO.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinsService::MyPinsService(IMyPinsRepository& myPinsRepository,
                                     MyPinsFileIO& myPinsFileIO,
                                     Eegeo::Pins::PinRepository& pinRepository,
                                     WorldPins::IWorldPinsFactory& pinFactory)
        : m_myPinsRepository(myPinsRepository)
        , m_myPinsFileIO(myPinsFileIO)
        , m_pinRepository(pinRepository)
        , m_pinFactory(pinFactory)
        , m_lastIdUsed(0)
        {
            
        }
        
        void MyPinsService::AddPin(const std::string& title,
                                   const std::string& description,
                                   const Eegeo::Space::LatLong& latLong,
                                   Byte* imageData,
                                   size_t imageSize,
                                   bool shouldShare)
        {
//            Eegeo::Pins::Pin* pin = m_pinFactory.CreatePin(latLong, 0);
//            m_pinRepository.AddPin(*pin);
            
//            MyPinModel *myPinModel = m_myPinModelFactory.CreateMyPinModel(title,
//                                                                          description,
//                                                                          imageData,
//                                                                          imageSize,
//                                                                          latLong,
//                                                                          shouldShare);
//            m_myPinsRepository.AddItem(*myPinModel);
//            
//            m_modelToPinIdMap.insert(std::make_pair(myPinModel, pin->GetId()));
        }
        
        void MyPinsService::RemovePin(const MyPinModel& myPinModel)
        {
            Eegeo::Pins::TPinId pinIdForModel = GetPinIdForModel(&myPinModel);
            Eegeo::Pins::Pin* pin = m_pinRepository.GetPinById(pinIdForModel);
            m_pinRepository.RemovePin(*pin);
            Eegeo_DELETE pin;
            
            m_myPinsRepository.RemoveItem(myPinModel);
        }
        
        Eegeo::Pins::TPinId MyPinsService::GetPinIdForModel(const MyPinModel *model)
        {
            TModelToPinIdMap::iterator it = m_modelToPinIdMap.find(model);
            Eegeo_ASSERT(it != m_modelToPinIdMap.end(), "Couldn't find pin for MyPinModel");
            return it->second;
        }
        
        void MyPinsService::SavePin(const std::string& title,
                                    const std::string& description,
                                    const Eegeo::Space::LatLong& latLong,
                                    Byte* imageData,
                                    size_t imageSize,
                                    bool shouldShare)
        {
            unsigned int idForThisPin = m_lastIdUsed++;
            
            std::string imagePath = "";

            if (imageData)
            {
                m_myPinsFileIO.TryCacheImageToDisk(imageData, imageSize, idForThisPin, imagePath);
            }
            
            m_myPinsFileIO.SavePinModelToDisk(idForThisPin, title, description, imagePath, latLong);
            
            if (shouldShare)
            {
                // Punt web request here...
            }
        }
    }
}