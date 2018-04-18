// Copyright eeGeo Ltd (2012-2018), All Rights Reserved



#include "MyPinCreationMenuOption.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationMenuOption::MyPinCreationMenuOption(Menu::View::IMenuViewModel& createPinContainerMenu,
                                                             MyPinCreation::View::IMyPinCreationConfirmationViewModel& myPinCreationConfirmationViewModel)
            : m_createPinContainerMenu(createPinContainerMenu)
            , m_myPinCreationConfirmationViewModel (myPinCreationConfirmationViewModel)
            {

            }

            MyPinCreationMenuOption::~MyPinCreationMenuOption()
            {

            }

            void MyPinCreationMenuOption::Select()
            {
                m_createPinContainerMenu.Close();
                m_myPinCreationConfirmationViewModel.Open();
            }
        }
    }
}
