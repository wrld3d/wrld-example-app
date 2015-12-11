// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISettingsMenuView.h"

#include "SettingsMenuViewIncludes.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SettingsMenu
    {
        namespace View
        {
            class SettingsMenuViewInterop : private Eegeo::NonCopyable, public ISettingsMenuView
            {
            private:
                SettingsMenuView* m_pView;

            public:
                SettingsMenuViewInterop(SettingsMenuView* pView)
                    : m_pView(pView)
                {
                }
            };
        }
    }
}
