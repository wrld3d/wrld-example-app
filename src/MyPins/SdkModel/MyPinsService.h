// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>

#include "MyPins.h"
#include "IMyPinsService.h"
#include "WorldPins.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsService : public IMyPinsService
            {
            public:
                MyPinsService(IMyPinsRepository& myPinsRepository,
                              MyPinsFileIO& myPinsFileIO,
                              IMyPinSelectionHandlerFactory& myPinSelectionHandlerFactory,
                              WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                              Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);


                void RemovePinWithId(const int myPinId);

                void SavePin(const std::string& title,
                             const std::string& description,
                             const Eegeo::Space::LatLong& latLong,
                             Byte* imageData,
                             size_t imageSize,
                             bool shouldShare);



            private:
                IMyPinsRepository& m_myPinsRepository;
                MyPinsFileIO& m_myPinsFileIO;
                IMyPinSelectionHandlerFactory& m_myPinSelectionHandlerFactory;

                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;

                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;

                Eegeo::Web::TWebLoadRequestCompletionCallback<ExampleApp::MyPins::SdkModel::MyPinsService> m_webRequestCompleteCallback;
                void WebRequestCompleteCallback(Eegeo::Web::IWebLoadRequest& webLoadRequest);

                unsigned int m_lastIdUsed;

                typedef std::map<MyPinModel*, WorldPins::SdkModel::WorldPinItemModel*> TMyPinToWorldPinMap;
                TMyPinToWorldPinMap m_myPinToWorldPinMap;

                void AddPinToMap(MyPinModel* pMyPinModel);

                void SubmitPinToWebService(const MyPinModel& myPinModel);

                MyPinModel* GetPinWithId(int pinId);
            };
        }
    }
}
