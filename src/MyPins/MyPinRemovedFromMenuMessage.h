// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinRemovedFromMenuMessage
        {
        public:
            MyPinRemovedFromMenuMessage(MyPinModel* myPinModel);
            
            MyPinModel* GetMyPinModel() const;
        private:
            MyPinModel* m_pMyPinModel;
        };
    }
}
