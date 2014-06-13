// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "RequestCurrentThemeNameMessage.h"

using namespace Examples;

RequestCurrentThemeNameMessage::RequestCurrentThemeNameMessage(JavaHudCrossThreadCommunicationExample* pExample)
	: AndroidExampleMessage(pExample)
{
}

bool RequestCurrentThemeNameMessage::Handle(JavaHudCrossThreadCommunicationExample& dispatcher) const
{
	;
	dispatcher.PostCurrentThemeNameToHud();
	return false;
}
