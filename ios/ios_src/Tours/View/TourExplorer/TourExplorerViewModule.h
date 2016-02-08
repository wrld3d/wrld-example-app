// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "TourExplorerViewIncludes.h"
#include "Rendering.h"
#include "Tours.h"
#include "ITourExplorerViewModule.h"
#include "BidirectionalBus.h"
#include "TourExplorerViewController.h"
#include "URLRequestHandler.h"

@class ImageStore;

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourExplorerViewModule: public ITourExplorerViewModule, private Eegeo::NonCopyable
                {
                private:
                    TourExplorerView* m_pView;
                    TourExplorerViewController* m_pViewController;
                    
                public:
                    TourExplorerViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                           ITourExplorerViewModel& viewModel,
                                           URLRequest::View::URLRequestHandler& urlRequestHandler,
                                           ITourExplorerCompositeViewController& tourExplorerCompositeViewController,
                                           const Eegeo::Rendering::ScreenProperties& screenProperties,
                                           ImageStore* pImageStore);
                    
                    ~TourExplorerViewModule();
                    
                    TourExplorerView& GetTourExplorerView() const;
                };
            }
        }
    }
}
