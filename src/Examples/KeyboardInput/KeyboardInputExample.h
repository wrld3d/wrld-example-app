//
//  KeyboardInputExample.h
//  ExampleApp
//
//  Created by Stephen Phillips on 18/07/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__KeyboardInputExample__
#define __ExampleApp__KeyboardInputExample__

#include <string>

#include "IExample.h"
#include "KeyboardInput.h"
#include "IKeyboardInputDismissedHandler.h"
#include "IKeyboardInputKeyPressedHandler.h"

namespace Examples
{
    class KeyboardInputExample : public IExample, public Eegeo::UI::NativeInput::IKeyboardInputDismissedHandler, public Eegeo::UI::NativeInput::IKeyboardInputKeyPressedHandler
    {
    private:
        Eegeo::UI::NativeInput::IKeyboardInput *m_pKeyboardInput;
        Eegeo::UI::NativeInput::IKeyboardInputFactory& keyboardInputFactory;
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        
    public:
        KeyboardInputExample(Eegeo::UI::NativeInput::IKeyboardInputFactory& keyboardInputFactory,
                             Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);
        
        static std::string GetName() { return "KeyboardInputExample"; }
        std::string Name() const { return GetName(); }
        
        void Start();
        void Update(float dt) {}
        void Draw() {}
        void Suspend();
        
        void HandleKeyboardInputDismissed();
        bool HandleKeyboardInputKeyPressed(const AppInterface::KeyboardData& data);
    };
}

#endif /* defined(__ExampleApp__KeyboardInputExample__) */
