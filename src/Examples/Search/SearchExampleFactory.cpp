//
//  SearchExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "SearchExampleFactory.h"
#include "SearchExample.h"

using namespace Examples;

SearchExampleFactory::SearchExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* SearchExampleFactory::CreateExample() const
{
    Eegeo_ASSERT(m_world.IsSearchServiceAvailable(), "Cannot run Search example, you must set up here.com Credentials");
    
    return new Examples::SearchExample(m_world.GetSearchService(),
                                       m_world.GetInterestPointProvider());
}
