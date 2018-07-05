#include "NavWidgetLocationSetHandler.h"
#include "NavWidgetView.h"
#include "NavWidgetSearchController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetLocationSetHandler::NavWidgetLocationSetHandler(NavWidgetView* pView, NavWidgetSearchController* pSearchController)
            : m_pView(pView)
            , m_pSearchController(pSearchController)
            , m_locationSetCallback(this, &NavWidgetLocationSetHandler::HandleLocationSet)
            {
                m_pView->InsertLocationSetCallback(m_locationSetCallback);
            }
            
            NavWidgetLocationSetHandler::~NavWidgetLocationSetHandler()
            {
                m_pView->RemoveLocationSetCallback(m_locationSetCallback);
            }
            
            void NavWidgetLocationSetHandler::HandleLocationSet(const bool& wasStartLocation)
            {
                [m_pSearchController handleLocationSet: wasStartLocation];
            }
        }
    }
}
