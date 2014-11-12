// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapInFocusScreenControl.h"

namespace ExampleApp
{
namespace SearchResultOnMap
{
SearchResultOnMapInFocusScreenControl::SearchResultOnMapInFocusScreenControl(Eegeo::Helpers::TIdentity identity)
	: ScreenControlViewModel::ScreenControlViewModelBase(false)
	, m_identity(identity)
{
}

Eegeo::Helpers::TIdentity SearchResultOnMapInFocusScreenControl::GetIdentity() const
{
	return m_identity;
}
}
}
