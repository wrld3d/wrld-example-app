/*
 * ToggleRouteMatchingMessage.cpp
 */

#include "ToggleRouteMatchingMessage.h"

using namespace Examples;

ToggleRouteMatchingMessage::ToggleRouteMatchingMessage(Examples::AndroidRouteMatchingExampleView* pExample)
	: AndroidExampleMessage(pExample)
{
}

bool ToggleRouteMatchingMessage::Handle(AndroidRouteMatchingExampleView& dispatcher) const
{
	dispatcher.ToggleMatching();
	return false;
}
