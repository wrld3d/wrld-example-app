// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewRemovePinMessage.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {

        MyPinDetailsViewRemovePinMessage::MyPinDetailsViewRemovePinMessage(int myPinModelId)
            : m_myPinModelId(myPinModelId)
        {

        }

        MyPinDetailsViewRemovePinMessage::~MyPinDetailsViewRemovePinMessage()
        {

        }

        int MyPinDetailsViewRemovePinMessage::GetMyPinModelId() const
        {
            return m_myPinModelId;
        }
    }
}