// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlViewModel.h"
#include "IOpenableControlViewModel.h"
#include "IMenuSectionsViewModel.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class IMenuViewModel
                : public ScreenControl::View::IScreenControlViewModel
                , public OpenableControl::View::IOpenableControlViewModel
                , public IMenuSectionsViewModel
            {
            public:
                virtual ~IMenuViewModel() { }
            };
        }
    }
}
