// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinRemovedFromMenuMessage
        {
        public:
            MyPinRemovedFromMenuMessage(SdkModel::MyPinModel* myPinModel);

            SdkModel::MyPinModel* GetMyPinModel() const;
        private:
            SdkModel::MyPinModel* m_pMyPinModel;
        };
    }
}
