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
            NavWidgetMenuOption::NavWidgetMenuOption(SdkModel::INavRoutingModel& routingModel,
                                                     SdkModel::NavRoutingController& routingController)
                    : m_routingModel(routingModel)
                    , m_routingController(routingController)
            {

            }

            NavWidgetMenuOption::~NavWidgetMenuOption()
            {

            }

            void NavWidgetMenuOption::Select()
            {
                //FROM NavRoutingController::OnDirectionsButtonClicked - this is ideal
                SdkModel::NavRoutingLocationModel startLocation;
                if (!m_routingController.TryGetCurrentLocation(startLocation))
                {
                    return;
                }

                m_routingModel.SetStartLocation(startLocation);
                m_routingModel.ClearEndLocation();

                m_routingController.OpenViewWithModel(m_routingModel);
            }
        }
    }
}