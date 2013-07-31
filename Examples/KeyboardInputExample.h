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
        
    public:
        KeyboardInputExample(Eegeo::UI::NativeInput::IKeyboardInputFactory& keyboardInputFactory);
        
        void Start();
        void Update() {}
        void Draw() {}
        void Suspend() {}
        
        void HandleKeyboardInputDismissed();
        void HandleKeyboardInputKeyPressed(const AppInterface::KeyboardData& data);
    };
}

#endif /* defined(__ExampleApp__KeyboardInputExample__) */
