// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInputDelegate.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "InputController.h"

AppInputDelegate::AppInputDelegate(const std::shared_ptr<ExampleApp::InputController>& inputController)
    :m_inputController(inputController)
{

}

AppInputDelegate::~AppInputDelegate()
{

}

void AppInputDelegate::Event_TouchRotate(const AppInterface::RotateData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchRotate(data);
}

void AppInputDelegate::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchRotate_Start(data);
}

void AppInputDelegate::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchRotate_End(data);
}

void AppInputDelegate::Event_TouchPinch(const AppInterface::PinchData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchPinch(data);
}

void AppInputDelegate::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchPinch_Start(data);
}

void AppInputDelegate::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchPinch_End(data);
}

void AppInputDelegate::Event_TouchPan(const AppInterface::PanData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchPan(data);
}

void AppInputDelegate::Event_TouchPan_Start(const AppInterface::PanData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchPan_Start(data);
}

void AppInputDelegate::Event_TouchPan_End(const AppInterface::PanData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchPan_End(data);
}

void AppInputDelegate::Event_TouchTap(const AppInterface::TapData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchTap(data);
}

void AppInputDelegate::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchDoubleTap(data);
}

void AppInputDelegate::Event_TouchDown(const AppInterface::TouchData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchDown(data);
}

void AppInputDelegate::Event_TouchMove(const AppInterface::TouchData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchMove(data);
}

void AppInputDelegate::Event_TouchUp(const AppInterface::TouchData& data)
{
    ASSERT_NATIVE_THREAD

    m_inputController->Event_TouchUp(data);
}

