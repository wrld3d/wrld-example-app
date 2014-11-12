// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassViewModel.h"

namespace ExampleApp
{
namespace Compass
{
CompassViewModel::CompassViewModel(Eegeo::Helpers::TIdentity identity,
                                   bool initiallyOnScreen)
	: m_screenControl(initiallyOnScreen, identity)
{

}

/*void CompassViewModel::UpdateHeadingAngleRadians(float headingRadians)
{
    m_updateCallbacks.ExecuteCallbacks(headingRadians);
}

void CompassViewModel::InsertUpdateCallback(Eegeo::Helpers::ICallback1<float>& updateCallback)
{
    m_updateCallbacks.AddCallback(updateCallback);
}

void CompassViewModel::RemoveUpdateCallback(Eegeo::Helpers::ICallback1<float>& updateCallback)
{
    m_updateCallbacks.RemoveCallback(updateCallback);
}*/

ScreenControlViewModel::IScreenControlViewModel& CompassViewModel::GetScreenControlViewModel()
{
	return m_screenControl;
}

Eegeo::Helpers::TIdentity CompassViewModel::GetIdentity() const
{
	return m_screenControl.GetIdentity();
}

void CompassViewModel::AddToScreen()
{
	m_screenControl.AddToScreen();
}

void CompassViewModel::RemoveFromScreen()
{
	m_screenControl.RemoveFromScreen();
}

void CompassViewModel::UpdateOnScreenState(float onScreenState)
{
	m_screenControl.UpdateOnScreenState(onScreenState);
}

void CompassViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
{
	m_screenControl.InsertOnScreenStateChangedCallback(callback);
}

void CompassViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControlViewModel::IScreenControlViewModel&, float>& callback)
{
	m_screenControl.RemoveOnScreenStateChangedCallback(callback);
}

bool CompassViewModel::IsFullyOffScreen() const
{
	return m_screenControl.IsFullyOffScreen();
}

bool CompassViewModel::IsFullyOnScreen() const
{
	return m_screenControl.IsFullyOnScreen();
}

float CompassViewModel::OnScreenState() const
{
	return m_screenControl.OnScreenState();
}
}
}
