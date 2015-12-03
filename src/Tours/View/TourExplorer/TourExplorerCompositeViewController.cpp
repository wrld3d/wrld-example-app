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
                                                                                         Menu::View::IMenuViewModel& secondaryMenuViewModel,
                                                                                         Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                                         ScreenControl::View::IScreenControlViewModel& compassViewModel,
                                                                                         ScreenControl::View::IScreenControlViewModel& flattenViewModel,
                                                                                         ScreenControl::View::IScreenControlViewModel& myPinCreationViewModel,
                                                                                         ScreenControl::View::IScreenControlViewModel& watermarkViewModel)
                : m_tourExplorerViewModel(tourExplorerViewModel)
                , m_secondaryMenuViewModel(secondaryMenuViewModel)
                , m_searchMenuViewModel(searchMenuViewModel)
                , m_compassViewModel(compassViewModel)
                , m_flattenViewModel(flattenViewModel)
                , m_myPinCreationViewModel(myPinCreationViewModel)
                , m_watermarkViewModel(watermarkViewModel)
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
                    
                    m_secondaryMenuViewModel.RemoveFromScreen();
                    m_searchMenuViewModel.RemoveFromScreen();
                    
                    m_compassViewModel.RemoveFromScreen();
                    m_flattenViewModel.RemoveFromScreen();
                    m_myPinCreationViewModel.RemoveFromScreen();
                    
                }
                
                void TourExplorerCompositeViewController::CloseTourExplorer()
                {
                    if(m_tourExplorerOpen)
                    {
                        m_tourExplorerOpen = false;
                        m_tourExplorerViewModel.RemoveFromScreen();
                        
                        m_secondaryMenuViewModel.AddToScreen();
                        m_searchMenuViewModel.AddToScreen();
                        m_compassViewModel.AddToScreen();
                        m_flattenViewModel.AddToScreen();
                        m_myPinCreationViewModel.AddToScreen();
                    }
                }
            }
        }
    }
}
