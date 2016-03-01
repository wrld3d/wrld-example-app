// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerCompositeViewController.h"
#include "ITourExplorerViewModel.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourExplorerCompositeViewController::TourExplorerCompositeViewController(ITourExplorerViewModel& tourExplorerViewModel,
                                                                                         Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                                         Menu::View::IMenuViewModel& settingsMenuViewModel,
                                                                                         ScreenControl::View::IScreenControlViewModel& watermarkViewModel)
                : m_tourExplorerViewModel(tourExplorerViewModel)
                , m_searchMenuViewModel(searchMenuViewModel)
                , m_settingsMenuViewModel(searchMenuViewModel)
                , m_tourExplorerOpen(false)
                {
                    
                }
                
                TourExplorerCompositeViewController::~TourExplorerCompositeViewController()
                {
                    
                }
                
                void TourExplorerCompositeViewController::OpenTourExplorer(const SdkModel::TourModel& tourModel, const int startAtCard, bool showBackButton)
                {
                    m_tourExplorerOpen = true;
                    m_tourExplorerViewModel.SetCurrentTour(tourModel);
                    m_tourExplorerViewModel.SetInitialCard(startAtCard);
                    m_tourExplorerViewModel.SetShowBackButton(showBackButton);
                    m_tourExplorerViewModel.AddToScreen();
                   
                    m_searchMenuViewModel.RemoveFromScreen();
                    m_settingsMenuViewModel.RemoveFromScreen();
                    
                }
                
                void TourExplorerCompositeViewController::CloseTourExplorer()
                {
                    if(m_tourExplorerOpen)
                    {
                        m_tourExplorerOpen = false;
                        m_tourExplorerViewModel.RemoveFromScreen();
                        
                        m_searchMenuViewModel.AddToScreen();
                        m_settingsMenuViewModel.AddToScreen();
                    }
                }
            }
        }
    }
}
