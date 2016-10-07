// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInputDelegate.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "InputController.h"
#include "AndroidInputHandler.h"
#include "AndroidInputProcessor.h"

AppInputDelegate::AppInputDelegate(const std::shared_ptr<ExampleApp::IInputController>& inputController,
								   const std::shared_ptr<Eegeo::Android::Input::AndroidInputProcessor>& inputProcessor,
								   const std::shared_ptr<Eegeo::Android::Input::IAndroidInputHandler>& inputHandler)
    :m_inputController(inputController)
    ,m_inputProcessor(inputProcessor)
    ,m_inputHandler(inputHandler)
{
	Eegeo_ASSERT(m_inputController != nullptr);
	Eegeo_ASSERT(m_inputProcessor != nullptr);
	Eegeo_ASSERT(m_inputHandler != nullptr);
	std::dynamic_pointer_cast<Eegeo::Android::Input::AndroidInputHandler>(m_inputHandler)->AddDelegateInputHandler(this);
}

AppInputDelegate::~AppInputDelegate()
{
	std::dynamic_pointer_cast<Eegeo::Android::Input::AndroidInputHandler>(m_inputHandler)->RemoveDelegateInputHandler(this);
}

void AppInputDelegate::HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
	ASSERT_NATIVE_THREAD
	m_inputProcessor->HandleInput(event);
}

void AppInputDelegate::Update(float dt)
{
	ASSERT_NATIVE_THREAD
	m_inputProcessor->Update(dt);
}

void AppInputDelegate::SetViewportOffset(float x, float y)
{
	ASSERT_NATIVE_THREAD
	std::dynamic_pointer_cast<Eegeo::Android::Input::AndroidInputHandler>(m_inputHandler)->SetViewportOffset(x,y);
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
