//
//  SearchExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "SearchExampleFactory.h"
#include "SearchExample.h"
#include "Logger.h"

using namespace Examples;

SearchExampleFactory::SearchExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* SearchExampleFactory::CreateExample() const
{
    if(!m_world.IsSearchServiceAvailable())
    {
        EXAMPLE_LOG("Cannot run Search example, you must set up here.com credentials\n");
        return NULL;
    }
    
    return new Examples::SearchExample(m_world.GetSearchService(),
                                       m_world.GetInterestPointProvider());
}

std::string SearchExampleFactory::ExampleName() const
{
	return Examples::SearchExample::GetName();
}

