/*
 * RequestCurrentThemeNameMessage.cpp
 */

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
