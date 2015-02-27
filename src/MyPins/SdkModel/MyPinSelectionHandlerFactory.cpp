// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectionHandlerFactory.h"
#include "MyPinSelectionHandler.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinSelectionHandlerFactory::MyPinSelectionHandlerFactory(MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository)
            : m_myPinBoundObjectRepository(myPinBoundObjectRepository)
            {
                
            }
            
            MyPinSelectionHandler* MyPinSelectionHandlerFactory::CreateMyPinSelectionHandler(MyPinModel& myPinModel) const
            {
                return Eegeo_NEW(MyPinSelectionHandler)(myPinModel, m_myPinBoundObjectRepository);
            }
        }
    }
}
