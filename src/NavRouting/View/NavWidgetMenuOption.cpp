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
                m_routingModel.ClearEndLocation();
                if (!m_routingModel.SetStartLocationFromCurrentPosition()) {
                    m_routingModel.ClearStartLocation();
                }

                m_routingController.OpenViewWithModel(m_routingModel);
            }
        }
    }
}
