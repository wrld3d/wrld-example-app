// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinRemovedFromMenuMessage
        {
        public:
            MyPinRemovedFromMenuMessage(SdkModel::MyPinModel::TPinIdType myPinId);

            SdkModel::MyPinModel::TPinIdType GetMyPinId() const;
        private:
            SdkModel::MyPinModel::TPinIdType m_myPinId;
        };
    }
}
