// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectionHandler.h"
#include "IMyPinBoundObjectRepository.h"
#include "FlurryWrapper.h"
#include "IMyPinBoundObject.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinSelectionHandler::MyPinSelectionHandler(MyPinModel& myPinModel,
                                                         MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository)
                : m_myPinModel(myPinModel)
                , m_myPinBoundObjectRepository(myPinBoundObjectRepository)
            {

            }

            void MyPinSelectionHandler::SelectPin()
            {
                FLURRY_SET_EVENT("Selected MyPin", "Name", m_myPinModel.GetTitle().c_str());
                IMyPinBoundObject& myPinBoundObject(m_myPinBoundObjectRepository.GetBoundObjectForPin(m_myPinModel));
                myPinBoundObject.HandlePinSelected(m_myPinModel);
            }
        }
    }
}
