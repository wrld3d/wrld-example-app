// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "Menu.h"
#include "ScreenControlViewModelIncludes.h"
#include "ITourExplorerCompositeViewController.h"
#include "Types.h"
#include <memory>

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
                    const std::shared_ptr<ITourExplorerViewModel> m_tourExplorerViewModel;
                    const std::shared_ptr<Menu::View::IMenuViewModel> m_searchMenuViewModel;
                    const std::shared_ptr<Menu::View::IMenuViewModel> m_settingsMenuViewModel;
                    bool m_tourExplorerOpen;
                    
                public:
                    TourExplorerCompositeViewController(const std::shared_ptr<ITourExplorerViewModel>& tourExplorerViewModel,
                                                        const std::shared_ptr<Menu::View::IMenuViewModel>& searchMenuViewModel,
                                                        const std::shared_ptr<Menu::View::IMenuViewModel>& settingsMenuViewModel,
                                                        const std::shared_ptr<ScreenControl::View::IScreenControlViewModel>& watermarkViewModel);
                    
                    ~TourExplorerCompositeViewController();
                    
                    void OpenTourExplorer(const SdkModel::TourModel& tourModel, const int startAtCard, bool showBackButton);
                    
                    void CloseTourExplorer();
                };
            }
        }
    }
}
