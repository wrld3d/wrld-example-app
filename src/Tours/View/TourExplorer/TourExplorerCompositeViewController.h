// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "Menu.h"
#include "ScreenControlViewModelIncludes.h"
#include "ITourExplorerCompositeViewController.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourExplorerCompositeViewController : public ITourExplorerCompositeViewController, private Eegeo::NonCopyable
                {
                    ITourExplorerViewModel& m_tourExplorerViewModel;
                    Menu::View::IMenuViewModel& m_searchMenuViewModel;
                    Menu::View::IMenuViewModel& m_settingsMenuViewModel;
                    bool m_tourExplorerOpen;
                    
                public:
                    TourExplorerCompositeViewController(ITourExplorerViewModel& tourExplorerViewModel,
                                                        Menu::View::IMenuViewModel& searchMenuViewModel,
                                                        Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                        ScreenControl::View::IScreenControlViewModel& watermarkViewModel);
                    
                    ~TourExplorerCompositeViewController();
                    
                    void OpenTourExplorer(const SdkModel::TourModel& tourModel, const int startAtCard, bool showBackButton);
                    
                    void CloseTourExplorer();
                };
            }
        }
    }
}
