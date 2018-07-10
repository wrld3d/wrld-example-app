// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModule.h"
#include "ScreenProperties.h"
#include "InteriorsExplorerView.h"
#include "InteriorsExplorerViewInterop.h"
#include "InteriorStreamingDialogView.h"
#include "InteriorStreamingDialogViewInterop.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewModule::InteriorsExplorerViewModule(SdkModel::InteriorsExplorerModel& model,
                                                                     InteriorsExplorerViewModel& viewModel,
                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                     Eegeo::Helpers::IdentityProvider& identityProvider,
                                                                     Eegeo::Location::NavigationService& navigationService,
                                                                     Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetTopPanelVisibleHeightChangedCallbacks,
                                                                     Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomPanelVisibleHeightChangedCallbacks)
            : m_navWidgetTopPanelVisibleHeightChangedCallback(this, &InteriorsExplorerViewModule::NavWidgetTopPanelVisibleHeightChanged)
            , m_navWidgetTopPanelVisibleHeightChangedCallbacks(m_navWidgetTopPanelVisibleHeightChangedCallbacks)
            , m_navWidgetBottomPanelVisibleHeightChangedCallback(this, &InteriorsExplorerViewModule::NavWidgetBottomPanelVisibleHeightChanged)
            , m_navWidgetBottomPanelVisibleHeightChangedCallbacks(m_navWidgetBottomPanelVisibleHeightChangedCallbacks)
            {
                const float screenWidth = screenProperties.GetScreenWidth();
                const float screenHeight = screenProperties.GetScreenHeight();
                const float pixelScale = screenProperties.GetPixelScale();
                
                m_pTutorialView = [[InteriorsExplorerTutorialView alloc] initWithParams: screenWidth : screenHeight : pixelScale];
                
                m_pView = [[InteriorsExplorerView alloc] initWithParams: screenWidth : screenHeight : pixelScale : *m_pTutorialView ];
                
                m_pStreamingDialogView = [[InteriorStreamingDialogView alloc] initWithParams: screenWidth : screenHeight : pixelScale ];
                
                m_pController = Eegeo_NEW(InteriorsExplorerController)(model,
                                                                       *[m_pView getInterop],
                                                                       viewModel,
                                                                       *[m_pStreamingDialogView getInterop],
                                                                       messageBus,
                                                                       navigationService);
                m_navWidgetTopPanelVisibleHeightChangedCallbacks.AddCallback(m_navWidgetTopPanelVisibleHeightChangedCallback);
                m_navWidgetBottomPanelVisibleHeightChangedCallbacks.AddCallback(m_navWidgetBottomPanelVisibleHeightChangedCallback);
            }
            
            InteriorsExplorerViewModule::~InteriorsExplorerViewModule()
            {
                m_navWidgetTopPanelVisibleHeightChangedCallbacks.RemoveCallback(m_navWidgetTopPanelVisibleHeightChangedCallback);
                m_navWidgetBottomPanelVisibleHeightChangedCallbacks.RemoveCallback(m_navWidgetBottomPanelVisibleHeightChangedCallback);
                Eegeo_DELETE m_pController;
                
                [m_pStreamingDialogView release];
                
                [m_pView release];
                
                [m_pTutorialView release];
            }
            
            InteriorsExplorerController& InteriorsExplorerViewModule::GetController() const
            {
                return *m_pController;
            }
            
            InteriorsExplorerView& InteriorsExplorerViewModule::GetView() const
            {
                return *m_pView;
            }
            
            InteriorsExplorerTutorialView& InteriorsExplorerViewModule::GetTutorialView() const
            {
                return *m_pTutorialView;
            }

            void InteriorsExplorerViewModule::NavWidgetTopPanelVisibleHeightChanged(NavRouting::View::INavWidgetView::THeight& newVisibleHeight)
            {
                [m_pView setNavigationModeFloorPanelTopBound: newVisibleHeight];
                [m_pView refreshFloorViews];
            }
            
            void InteriorsExplorerViewModule::NavWidgetBottomPanelVisibleHeightChanged(NavRouting::View::INavWidgetView::THeight& newVisibleHeight)
            {
                [m_pView setNavigationModeFloorPanelBottomBound: newVisibleHeight];
                [m_pView refreshFloorViews];
            }

            InteriorStreamingDialogView& InteriorsExplorerViewModule::GetStreamingDialogView() const
            {
                return *m_pStreamingDialogView;
            }
        }
    }
}
