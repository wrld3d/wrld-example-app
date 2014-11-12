// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MenuScreenControl.h"

namespace ExampleApp
{
namespace Menu
{
MenuScreenControl::MenuScreenControl(Eegeo::Helpers::TIdentity identity)
	: ScreenControlViewModel::ScreenControlViewModelBase(false)
	, m_identity(identity)
{
}

Eegeo::Helpers::TIdentity MenuScreenControl::GetIdentity() const
{
	return m_identity;
}
}
}
