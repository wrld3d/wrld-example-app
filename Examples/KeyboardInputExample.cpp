//
//  KeyboardInputExample.cpp
//  ExampleApp
//
//  Created by Stephen Phillips on 18/07/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "KeyboardInputExample.h"
#include "IKeyboardInputFactory.h"

using namespace Examples;
using namespace Eegeo::UI::NativeInput;

KeyboardInputExample::KeyboardInputExample(Eegeo::UI::NativeInput::IKeyboardInputFactory& keyboardInputFactory) :
keyboardInputFactory(keyboardInputFactory)
{
}

void KeyboardInputExample::Start()
{
    m_pKeyboardInput = keyboardInputFactory.CreateKeyboardInput(*this, *this, KeyboardTypeDefault, ReturnKeySearch);
}

void KeyboardInputExample::HandleKeyboardInputDismissed()
{
    Eegeo_TTY("%s", "\nDismissed the keyboard.");
}

void KeyboardInputExample::HandleKeyboardInputKeyPressed(const AppInterface::KeyboardData& data)
{
    if (data.printable)
    {
        Eegeo_TTY("%c", data.keyCode);
    }
    
    //Optionally dismiss the keyboard on pressing Return key
    if (data.keyCode == '\n')
    {
        m_pKeyboardInput->Dismiss();
    }
}
