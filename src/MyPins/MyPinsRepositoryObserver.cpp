// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsRepositoryObserver.h"
#include "MyPinsRepository.h"
#include "MyPinModel.h"
#include "MyPinsFileIO.h"
#include "MyPinAddedToMenuMessage.h"
#include "MyPinRemovedFromMenuMessage.h"

#include <string>
#include <sstream>

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinsRepositoryObserver::MyPinsRepositoryObserver(MyPinsRepository& myPinsRepository,
                                                           MyPinsFileIO& myPinsFileIO,
                                                           ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_myPinsRepository(myPinsRepository)
        , m_myPinsFileIO(myPinsFileIO)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_pinAddedCallback(this, &MyPinsRepositoryObserver::HandlePinAddedToRepository)
        , m_pinRemovedCallback(this, &MyPinsRepositoryObserver::HandlePinRemovedFromRepository)
        {
            m_myPinsRepository.InsertItemAddedCallback(m_pinAddedCallback);
            m_myPinsRepository.InsertItemRemovedCallback(m_pinRemovedCallback);
    
        }
        
        MyPinsRepositoryObserver::~MyPinsRepositoryObserver()
        {
            m_myPinsRepository.RemoveItemAddedCallback(m_pinAddedCallback);
            m_myPinsRepository.RemoveItemRemovedCallback(m_pinRemovedCallback);
        }
        
        void MyPinsRepositoryObserver::HandlePinAddedToRepository(MyPinModel*& myPinModel)
        {
        	m_nativeToUiMessageBus.Publish(MyPinAddedToMenuMessage(myPinModel));
        }
        
        void MyPinsRepositoryObserver::HandlePinRemovedFromRepository(MyPinModel*& myPinModel)
        {
            m_nativeToUiMessageBus.Publish(MyPinRemovedFromMenuMessage(myPinModel));
            
            std::vector<MyPinModel*> pinModels;
            pinModels.reserve(m_myPinsRepository.GetItemCount());
            
            for (int i = 0; i < m_myPinsRepository.GetItemCount(); ++i)
            {
                pinModels.push_back(m_myPinsRepository.GetItemAtIndex(i));
            }
            
            m_myPinsFileIO.SaveAllRepositoryPinsToDisk(pinModels);
        }
    }
}
