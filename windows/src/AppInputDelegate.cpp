// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInputDelegate.h"
#include "WindowsAppThreadAssertionMacros.h"

AppInputDelegate::AppInputDelegate(const std::shared_ptr<ExampleApp::IInputController>& inputController,
                                   const std::shared_ptr<Eegeo::Windows::Input::WindowsInputProcessor>& inputProcessor,
                                   const std::shared_ptr<Eegeo::Windows::Input::IWindowsInputHandler>& inputHandler)
: m_inputController(inputController)
, m_inputProcessor(inputProcessor)
, m_inputHandler(inputHandler)
{
    Eegeo_ASSERT(m_inputController != nullptr);
    Eegeo_ASSERT(m_inputProcessor != nullptr);
    Eegeo_ASSERT(m_inputHandler != nullptr);
    std::dynamic_pointer_cast<Eegeo::Windows::Input::WindowsInputHandler>(m_inputHandler)->AddDelegateInputHandler(this);
}

AppInputDelegate::~AppInputDelegate()
{
    std::dynamic_pointer_cast<Eegeo::Windows::Input::WindowsInputHandler>(m_inputHandler)->RemoveDelegateInputHandler(this);
}

void AppInputDelegate::HandleMouseInput(const Eegeo::Windows::Input::MouseInputEvent& event, float screenWidth, float screenHeight)
{
    m_inputProcessor->HandleMouseInput(event, screenWidth, screenHeight);
}

void AppInputDelegate::HandleMouseInput(const Eegeo::Windows::Input::KeyboardInputEvent& keyEvent)
{
    m_inputProcessor->HandleMouseInput(keyEvent);
}

void AppInputDelegate::HandleTouchScreenInput(const Eegeo::Windows::Input::TouchScreenInputEvent& event, float screenWidth, float screenHeight)
{
    m_inputProcessor->HandleTouchScreenInput(event, screenWidth, screenHeight);
}

void AppInputDelegate::SetAllInputEventsToPointerUp(int x, int y)
{
    m_inputProcessor->SetAllInputEventsToPointerUp(x, y);
}

void AppInputDelegate::SetTouchInputEventToPointerUp(int touchId)
{
    m_inputProcessor->SetTouchInputEventToPointerUp(touchId);
}

void AppInputDelegate::PopAllTouchEvents()
{
    m_inputProcessor->PopAllTouchEvents();
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

void AppInputDelegate::Update(float dt)
{
    ASSERT_NATIVE_THREAD
    m_inputProcessor->Update(dt);
}

void AppInputDelegate::SetViewportOffset(float x, float y)
{
    ASSERT_NATIVE_THREAD
    std::dynamic_pointer_cast<Eegeo::Windows::Input::WindowsInputHandler>(m_inputHandler)->SetViewportOffset(x, y);
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

void AppInputDelegate::Event_Zoom(const AppInterface::ZoomData& data)
{
    m_inputController->Event_Zoom(data);
}

void AppInputDelegate::Event_TiltStart(const AppInterface::TiltData& data)
{
    m_inputController->Event_TiltStart(data);
}

void AppInputDelegate::Event_TiltEnd(const AppInterface::TiltData& data)
{
    m_inputController->Event_TiltEnd(data);
}

void AppInputDelegate::Event_Tilt(const AppInterface::TiltData& data)
{
    m_inputController->Event_Tilt(data);
}

