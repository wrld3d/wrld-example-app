// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinVisibilityStateChangedHandlerFactory.h"
#include "MyPinVisibilityStateChangedHandler.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinVisibilityStateChangedHandlerFactory::MyPinVisibilityStateChangedHandlerFactory(const std::shared_ptr<MyPins::SdkModel::IMyPinBoundObjectRepository>& myPinBoundObjectRepository)
            : m_myPinBoundObjectRepository(myPinBoundObjectRepository)
            {
                
            }
            
            WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* MyPinVisibilityStateChangedHandlerFactory::CreateMyPinVisibilityStateChangedHandler(MyPinModel& myPinModel) const
            {
                return Eegeo_NEW(MyPinVisibilityStateChangedHandler)(myPinModel, *m_myPinBoundObjectRepository);
            }
        }
    }
}
