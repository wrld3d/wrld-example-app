/*
 * ActivateNextExampleMessage.cpp
 */

#include "ActivateNextExampleMessage.h"

using namespace Examples;

ActivateNextExampleMessage::ActivateNextExampleMessage(Examples::AndroidExampleControllerView* pExample)
	: AndroidExampleMessage(pExample)
{
}

bool ActivateNextExampleMessage::Handle(AndroidExampleControllerView& dispatcher) const
{
	dispatcher.SelectNext();
	return false;
}





