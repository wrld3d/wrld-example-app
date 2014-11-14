// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsRepositoryObserver.h"
#include "MyPinsRepository.h"
#include "IMenuOptionsModel.h"
#include "MyPinModel.h"
#include "MyPinMenuOption.h"

#include <string>
#include <sstream>

namespace ExampleApp
{
    namespace MyPins
    {
        template<typename T>
        std::string ConvertModelDetailToString(const T& detail)
        {
            std::stringstream ss;
            ss << detail;
            return ss.str();
        }
        
        MyPinsRepositoryObserver::MyPinsRepositoryObserver(MyPinsRepository& myPinsRepository,
                                                           Menu::IMenuOptionsModel& menuOptionsModel,
                                                           Menu::IMenuViewModel& menuViewModel,
                                                           ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        : m_myPinsRepository(myPinsRepository)
        , m_menuOptionsModel(menuOptionsModel)
        , m_menuViewModel(menuViewModel)
        , m_uiToNativeMessageBus(uiToNativeMessageBus)
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
            m_menuOptionsModel.AddItem(ConvertModelDetailToString(myPinModel->Identifier()),
                                       myPinModel->GetTitle(),
                                       "",
                                       "place",
                                       Eegeo_NEW(MyPinMenuOption)(*myPinModel, m_menuViewModel, m_uiToNativeMessageBus));
        }
        
        void MyPinsRepositoryObserver::HandlePinRemovedFromRepository(MyPinModel*& myPinModel)
        {
            m_menuOptionsModel.RemoveItem(ConvertModelDetailToString(myPinModel->Identifier()));
        }
    }
}