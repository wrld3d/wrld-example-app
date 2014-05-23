/*
 * RouteSimulationActionMessage.cpp
 */

#include "RouteSimulationActionMessage.h"

using namespace Examples;

RouteSimulationActionMessage::RouteSimulationActionMessage(Examples::AndroidRouteSimulationExampleView* pExample, Action action)
: AndroidExampleMessage(pExample)
, m_action(action)
{
}

bool RouteSimulationActionMessage::Handle(AndroidRouteSimulationExampleView& dispatcher) const
{
	(dispatcher.*m_action)();
	return false;
}
