// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
