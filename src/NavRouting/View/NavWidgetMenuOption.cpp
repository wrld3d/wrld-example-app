#include "NavWidgetMenuOption.h"
#include "BidirectionalBus.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetMenuOption::NavWidgetMenuOption(SdkModel::INavRoutingLocationFinder& locationFinder,
                                                     SdkModel::INavRoutingModel& routingModel,
                                                     SdkModel::NavRoutingController& routingController)
                    : m_locationFinder(locationFinder)
                    , m_routingModel(routingModel)
                    , m_routingController(routingController)
            {

            }

            NavWidgetMenuOption::~NavWidgetMenuOption()
            {

            }

            void NavWidgetMenuOption::Select()
            {
                SdkModel::NavRoutingLocationModel startLocation;
                if (!m_locationFinder.TryGetCurrentLocation(startLocation))
                {
                    return;
                }

                m_routingModel.ClearEndLocation();
                m_routingModel.SetStartLocation(startLocation);

                m_routingController.OpenViewWithModel(m_routingModel);
            }
        }
    }
}