// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#include "IMenuOption.h"


#include "MyPinCreation.h"
#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            class MyPinCreationMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                Menu::View::IMenuViewModel& m_createPinContainerMenu;
                MyPinCreation::View::IMyPinCreationConfirmationViewModel& m_myPinCreationConfirmationViewModel;

            public:
                MyPinCreationMenuOption(Menu::View::IMenuViewModel& createPinContainerMenu,MyPinCreation::View::IMyPinCreationConfirmationViewModel& myPinCreationConfirmationViewModel);

                ~MyPinCreationMenuOption();

                void Select();
            };
        }
    }
}
