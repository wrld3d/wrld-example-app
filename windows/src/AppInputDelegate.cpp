// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInputDelegate.h"
#include "WindowsAppThreadAssertionMacros.h"

AppInputDelegate::AppInputDelegate(ExampleApp::MobileExampleApp& exampleApp)
    :m_exampleApp(exampleApp)
{

}

AppInputDelegate::~AppInputDelegate()
{

}

void AppInputDelegate::Event_TouchRotate(const AppInterface::RotateData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchRotate(data);
}

void AppInputDelegate::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchRotate_Start(data);
}

void AppInputDelegate::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchRotate_End(data);
}

void AppInputDelegate::Event_TouchPinch(const AppInterface::PinchData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchPinch(data);
}

void AppInputDelegate::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchPinch_Start(data);
}

void AppInputDelegate::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchPinch_End(data);
}

void AppInputDelegate::Event_TouchPan(const AppInterface::PanData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchPan(data);
}

void AppInputDelegate::Event_TouchPan_Start(const AppInterface::PanData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchPan_Start(data);
}

void AppInputDelegate::Event_TouchPan_End(const AppInterface::PanData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchPan_End(data);
}

void AppInputDelegate::Event_TouchTap(const AppInterface::TapData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchTap(data);
}

void AppInputDelegate::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchDoubleTap(data);
}

void AppInputDelegate::Event_TouchDown(const AppInterface::TouchData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchDown(data);
}

void AppInputDelegate::Event_TouchMove(const AppInterface::TouchData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchMove(data);
}

void AppInputDelegate::Event_TouchUp(const AppInterface::TouchData& data)
{
    ASSERT_NATIVE_THREAD

    m_exampleApp.Event_TouchUp(data);
}

void AppInputDelegate::Event_Zoom(const AppInterface::ZoomData& data)
{
    m_exampleApp.Event_Zoom(data);
}

void AppInputDelegate::Event_TiltStart(const AppInterface::TiltData& data)
{
    m_exampleApp.Event_TiltStart(data);
}

void AppInputDelegate::Event_TiltEnd(const AppInterface::TiltData& data)
{
    m_exampleApp.Event_TiltEnd(data);
}

void AppInputDelegate::Event_Tilt(const AppInterface::TiltData& data)
{
    m_exampleApp.Event_Tilt(data);
}

