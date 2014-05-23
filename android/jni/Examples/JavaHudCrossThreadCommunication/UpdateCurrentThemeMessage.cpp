/*
 * UpdateCurrentThemeMessage.cpp
 */

#include "UpdateCurrentThemeMessage.h"

using namespace Examples;

UpdateCurrentThemeMessage::UpdateCurrentThemeMessage(
		JavaHudCrossThreadCommunicationExample* pExample,
		const std::string& themeName)
: AndroidExampleMessage(pExample)
, m_themeName(themeName)
{
}

bool UpdateCurrentThemeMessage::Handle(JavaHudCrossThreadCommunicationExample& dispatcher) const
{;
	dispatcher.SetCurrentThemeByName(m_themeName);
	return false;
}
