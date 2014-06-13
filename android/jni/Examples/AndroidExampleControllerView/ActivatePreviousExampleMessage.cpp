// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ActivatePreviousExampleMessage.h"

using namespace Examples;

ActivatePreviousExampleMessage::ActivatePreviousExampleMessage(Examples::AndroidExampleControllerView* pExample)
	: AndroidExampleMessage(pExample)
{
}

bool ActivatePreviousExampleMessage::Handle(AndroidExampleControllerView& dispatcher) const
{
	dispatcher.SelectPrevious();
	return false;
}
