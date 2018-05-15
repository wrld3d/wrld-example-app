// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModule.h"
#include "NavRoutingModel.h"
#include "NavRouteDrawingController.h"
#include "NavRoutingServiceController.h"
#include "NavWidgetRouteUpdateHandler.h"
#include "NavWidgetRouteDrawingHandler.h"
#include "NavRoutingController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingModule::NavRoutingModule(PolyLineArgs::IShapeService& shapeService,
                                               Eegeo::Routes::Webservice::IRoutingWebservice& routingWebservice,
                                               Eegeo::Location::ILocationService& locationService,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pNavRoutingModel = Eegeo_NEW(NavRoutingModel)();
                m_pNavRouteDrawingController = Eegeo_NEW(NavRouteDrawingController)(shapeService);
                m_pNavRoutingServiceController = Eegeo_NEW(NavRoutingServiceController)(routingWebservice);

                m_pRouteUpdateHandler = Eegeo_NEW(NavWidgetRouteUpdateHandler)(*m_pNavRoutingModel,
                                                                               *m_pNavRoutingServiceController);

                m_pRouteDrawingHandler = Eegeo_NEW(NavWidgetRouteDrawingHandler)(*m_pNavRoutingModel,
                                                                                 *m_pNavRouteDrawingController);

                m_pRoutingController = Eegeo_NEW(NavRoutingController)(*m_pNavRoutingModel,
                                                                       locationService,
                                                                       messageBus);
            }

            NavRoutingModule::~NavRoutingModule()
            {
                Eegeo_DELETE m_pRoutingController;
                Eegeo_DELETE m_pRouteDrawingHandler;
                Eegeo_DELETE m_pRouteUpdateHandler;
                Eegeo_DELETE m_pNavRouteDrawingController;
                Eegeo_DELETE m_pNavRoutingServiceController;
                Eegeo_DELETE m_pNavRoutingModel;
            }

            INavRouteDrawingController& NavRoutingModule::GetRouteDrawingController()
            {
                return *m_pNavRouteDrawingController;
            }

            INavRoutingServiceController& NavRoutingModule::GetRoutingServiceController()
            {
                return *m_pNavRoutingServiceController;
            }
        }
    }
}
