//
//  KeyboardInputExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "KeyboardInputExampleFactory.h"
#include "KeyboardInputExample.h"
#include "NativeUIFactories.h"

using namespace Examples;

KeyboardInputExampleFactory::KeyboardInputExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* KeyboardInputExampleFactory::CreateExample() const
{
    return new Examples::KeyboardInputExample(m_world.GetNativeUIFactories().IKeyboardInputFactory());
}

std::string KeyboardInputExampleFactory::ExampleName() const
{
	return Examples::KeyboardInputExample::GetName();
}

