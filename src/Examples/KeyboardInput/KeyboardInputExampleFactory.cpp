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

KeyboardInputExampleFactory::KeyboardInputExampleFactory(Eegeo::EegeoWorld& world,
                                                         Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
: m_world(world)
, m_globeCameraController(globeCameraController)
{
    
}

IExample* KeyboardInputExampleFactory::CreateExample() const
{
    return new Examples::KeyboardInputExample(m_world.GetNativeUIFactories().IKeyboardInputFactory(),
                                              m_globeCameraController);
}

std::string KeyboardInputExampleFactory::ExampleName() const
{
	return Examples::KeyboardInputExample::GetName();
}

