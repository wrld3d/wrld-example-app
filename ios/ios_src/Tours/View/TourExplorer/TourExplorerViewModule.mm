// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "TourExplorerViewModule.h"
#include "TourExplorerView.h"
#include "ScreenProperties.h"
#include "TourExplorerViewInterop.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourExplorerViewModule::TourExplorerViewModule(ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                                                               ITourExplorerViewModel& viewModel,
                                                               TourWebView* pWebView,
                                                               TourHovercard::ITourHovercardView& tourHoverCardView,
                                                               ITourExplorerCompositeViewController& tourExplorerCompositeViewController,
                                                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                               Metrics::IMetricsService& metricsService,
                                                               ImageStore* pImageStore)
                {
                    m_pView = [[TourExplorerView alloc] initWithParams
                               : screenProperties.GetScreenWidth()
                               : screenProperties.GetScreenHeight()
                               : screenProperties.GetPixelScale()
                               : pWebView
                               : pImageStore];
                    
                    m_pViewController = Eegeo_NEW(TourExplorerViewController)(viewModel,
                                                                              tourExplorerCompositeViewController,
                                                                              *[m_pView getInterop],
                                                                              tourHoverCardView,
                                                                              messageBus,
                                                                              metricsService);
                }
                
                TourExplorerViewModule::~TourExplorerViewModule()
                {
                    Eegeo_DELETE m_pViewController;
                    [m_pView release];
                }
                
                TourExplorerView& TourExplorerViewModule::GetTourExplorerView() const
                {
                    return *m_pView;
                }
            }
        }
    }
}
