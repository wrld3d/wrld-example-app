// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Menu.h"
#include "IPrimaryMenuViewModule.h"
#include "Rendering.h"
#include "Modality.h"
#include "MenuController.h"
#include "CustomTableDataProvider.h"

namespace ExampleApp
{
    namespace PrimaryMenu
    {
        namespace View
        {
            class PrimaryMenuViewModule: public IPrimaryMenuViewModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::MenuController* m_pController;
                PrimaryMenuView* m_pView;
                CustomTableDataProvider* m_pDataProvider;

            public:
                PrimaryMenuViewModule(Menu::View::IMenuModel& primaryMenuModel,
                                      Menu::View::IMenuViewModel& primaryMenuViewModel,
                                      const Eegeo::Rendering::ScreenProperties& screenProperties,
                                      Modality::View::IModalityModel& modalityModel);

                ~PrimaryMenuViewModule();

                Menu::View::MenuController& GetMenuController() const;

                PrimaryMenuView& GetPrimaryMenuView() const;
            };
        }
    }
}
