/*
 * ActivatePreviousExampleMessage.cpp
 */

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
