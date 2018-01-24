// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMenuViewModel.h"
#include "OpenableControlViewModelBase.h"
#include "ScreenControlViewModelBase.h"
#include "IMenuSectionViewModel.h"
#include "IIdentity.h"
#include "MenuOpenableControl.h"
#include "MenuScreenControl.h"
#include "MenuSectionsViewModel.h"
#include "Menu.h"
#include "Reaction.h"
#include <vector>

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class MenuViewModel : public IMenuViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_identity;
                MenuOpenableControl m_openViewModel;
                MenuScreenControl m_screenViewModel;
                MenuSectionsViewModel m_sectionsViewModel;

            public:
                MenuViewModel(bool isInitiallyOnScreen,
                              Eegeo::Helpers::TIdentity identity);

                Eegeo::Helpers::TIdentity GetIdentity() const;

                void AddToScreen();

                void RemoveFromScreen();

                void InsertOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback);

                void RemoveOnScreenStateChangedCallback(
                        Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback);

                bool IsOffScreen() const;

                bool IsOnScreen() const;

                void Open();

                void Close();

                bool IsOpen() const;

                bool IsClosed() const;

                void InsertOpenStateChangedCallback(Eegeo::Helpers::ICallback1<OpenableControl::View::IOpenableControlViewModel&>& callback);

                void RemoveOpenStateChangedCallback(Eegeo::Helpers::ICallback1<OpenableControl::View::IOpenableControlViewModel&>& callback);

                void AddSection(IMenuSectionViewModel& section);
                void RemoveSection(IMenuSectionViewModel& section);

                size_t SectionsCount() const
                {
                    return m_sectionsViewModel.SectionsCount();
                }

                size_t NumberOfCells() const
                {
                    return m_sectionsViewModel.NumberOfCells();
                }

                IMenuSectionViewModel& GetMenuSection(int index) const;
            };
        }
    }
}
