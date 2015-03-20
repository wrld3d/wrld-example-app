// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinVisibilityStateChangedHandler.h"
#include "IMyPinBoundObjectRepository.h"
#include "IMyPinBoundObject.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinVisibilityStateChangedHandler::MyPinVisibilityStateChangedHandler(MyPinModel& myPinModel,
                                                                                   MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository)
            : m_myPinModel(myPinModel)
            , m_myPinBoundObjectRepository(myPinBoundObjectRepository)
            {
                
            }
            
            MyPinVisibilityStateChangedHandler::~MyPinVisibilityStateChangedHandler()
            {
                
            }
            
            void MyPinVisibilityStateChangedHandler::HandlePinBecameFullyVisible()
            {
                IMyPinBoundObject& myPinBoundObject(m_myPinBoundObjectRepository.GetBoundObjectForPin(m_myPinModel));
                myPinBoundObject.HandlePinBecameFullyVisible(m_myPinModel);
            }
            
            void MyPinVisibilityStateChangedHandler::HandlePinBecameFullyInvisible()
            {
                IMyPinBoundObject& myPinBoundObject(m_myPinBoundObjectRepository.GetBoundObjectForPin(m_myPinModel));
                myPinBoundObject.HandlePinBecameFullyInvisible(m_myPinModel);
            }
        }
    }
}
