// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsService.h"
#include "IMyPinsRepository.h"
#include "PinRepository.h"
#include "IWorldPinsFactory.h"
#include "Pin.h"
#include "MyPinsFileIO.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "ImageUploadData.h"
#include "IMenuOptionsModel.h"
#include "MyPinMenuOption.h"
#include "IWorldPinsService.h"
#include "WorldPinFocusData.h"

#include <string>
#include <sstream>

namespace ExampleApp
{
    namespace MyPins
    {

        
        MyPinsService::MyPinsService(IMyPinsRepository& myPinsRepository,
                                     MyPinsFileIO& myPinsFileIO,
                                     WorldPins::IWorldPinsService& worldPinsService,
                                     Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory)
        : m_myPinsRepository(myPinsRepository)
        , m_myPinsFileIO(myPinsFileIO)
        , m_worldPinsService(worldPinsService)
        , m_webLoadRequestFactory(webLoadRequestFactory)
        , m_lastIdUsed(m_myPinsFileIO.GetLastIdWrittenToDisk())
        , m_webRequestCompleteCallback(this, &MyPinsService::WebRequestCompleteCallback)
        {
            std::vector<MyPinModel*> pinModels;
            m_myPinsFileIO.LoadPinModelsFromDisk(pinModels);
            
            for (std::vector<MyPinModel*>::iterator it = pinModels.begin(); it != pinModels.end(); ++it)
            {
                m_myPinsRepository.AddItem(*it);
                AddPinToMap(*it);
            }
        }
        
        void MyPinsService::AddPinToMap(MyPinModel* pMyPinModel)
        {
            WorldPins::WorldPinFocusData worldPinFocusData(pMyPinModel->GetTitle(), pMyPinModel->GetDescription());
            WorldPins::WorldPinItemModel* worldPinItemModel = m_worldPinsService.AddPin(pMyPinModel, worldPinFocusData, pMyPinModel->GetLatLong(), 0);
            m_myPinToWorldPinMap.insert(std::make_pair(pMyPinModel, worldPinItemModel));
        }
        
        void MyPinsService::RemovePin(MyPinModel* myPinModel)
        {
            TMyPinToWorldPinMap::iterator it = m_myPinToWorldPinMap.find(myPinModel);
            
            if (it != m_myPinToWorldPinMap.end())
            {
                WorldPins::WorldPinItemModel* worldPinItemModel = it->second;
                m_worldPinsService.RemovePin(worldPinItemModel);
                
                m_myPinsRepository.RemoveItem(myPinModel);
                m_myPinToWorldPinMap.erase(it);
                Eegeo_DELETE myPinModel;
            }
        }
        
        void MyPinsService::SavePin(const std::string& title,
                                    const std::string& description,
                                    const Eegeo::Space::LatLong& latLong,
                                    Byte* imageData,
                                    size_t imageSize,
                                    bool shouldShare)
        {
            unsigned int idForThisPin = ++m_lastIdUsed;
            std::string imagePath = "";

            if (imageData)
            {
                m_myPinsFileIO.TryCacheImageToDisk(imageData, imageSize, idForThisPin, imagePath);
            }
            
            MyPinModel *pinModel = Eegeo_NEW(MyPinModel)(idForThisPin,
                                                         title,
                                                         description,
                                                         imagePath,
                                                         latLong);
            
            m_myPinsFileIO.SavePinModelToDisk(*pinModel);
            
            if (shouldShare)
            {
                SubmitPinToWebService(*pinModel);
            }
            
            m_myPinsRepository.AddItem(pinModel);
            AddPinToMap(pinModel);
        }
        
        void MyPinsService::SubmitPinToWebService(const ExampleApp::MyPins::MyPinModel &myPinModel)
        {
            Eegeo_TTY("Here is where you submit pin to web service\n");
        }
        
        void MyPinsService::WebRequestCompleteCallback(Eegeo::Web::IWebLoadRequest& webLoadRequest)
        {
            Eegeo_TTY("Web Request Completed, code: %d\n", webLoadRequest.HttpStatusCode());
        }
    }
}
