// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassScreenControl.h"

namespace ExampleApp
{
namespace Compass
{
CompassScreenControl::CompassScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
	: ScreenControlViewModel::ScreenControlViewModelBase(initiallyOnScreen)
	, m_identity(identity)
{
}

Eegeo::Helpers::TIdentity CompassScreenControl::GetIdentity() const
{
	return m_identity;
}
}
}
