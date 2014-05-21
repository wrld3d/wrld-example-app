//
//  ControlCityThemeExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "ControlCityThemeExampleFactory.h"
#include "ControlCityThemeExample.h"

using namespace Examples;

ControlCityThemeExampleFactory::ControlCityThemeExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* ControlCityThemeExampleFactory::CreateExample() const
{
    return new Examples::ControlCityThemeExample(m_world.GetCityThemesService(),
                                                 m_world.GetCityThemesRepository(),
                                                 m_world.GetCityThemesUpdater(),
                                                 m_world);
}
