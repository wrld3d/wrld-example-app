/*
 * RouteSimulationActionMessage.h
 */

#ifndef ROUTESIMULATIONACTIONMESSAGE_H_
#define ROUTESIMULATIONACTIONMESSAGE_H_

#include "AndroidRouteSimulationExampleView.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
class RouteSimulationActionMessage : public AndroidExampleMessage<AndroidRouteSimulationExampleView>
{
	typedef void (AndroidRouteSimulationExampleView::*Action)();
	Action m_action;

public:
	RouteSimulationActionMessage(Examples::AndroidRouteSimulationExampleView* pExample, Action action);

	virtual bool Handle(AndroidRouteSimulationExampleView& dispatcher) const;
};
}



#endif /* ROUTESIMULATIONACTIONMESSAGE_H_ */
