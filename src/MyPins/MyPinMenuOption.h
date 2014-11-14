// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMenuOption.h"
#include "MyPinModel.h"

#include <string>

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinMenuOption : public Menu::IMenuOption
        {
        public:
            MyPinMenuOption(MyPinModel myPinModel)
            : m_myPinModel(myPinModel)
            {
                
            }
            
            void Select()
            {
                Eegeo_TTY("Selected %s\n", m_myPinModel.GetTitle().c_str());
            }
        private:
            MyPinModel m_myPinModel;
            
        };
    }
}