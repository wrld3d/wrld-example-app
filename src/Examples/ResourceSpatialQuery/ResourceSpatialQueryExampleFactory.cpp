//
//  ResourceSpatialQueryExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "ResourceSpatialQueryExampleFactory.h"
#include "ResourceSpatialQueryExample.h"

using namespace Examples;

ResourceSpatialQueryExampleFactory::ResourceSpatialQueryExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* ResourceSpatialQueryExampleFactory::CreateExample() const
{
    return new Examples::ResourceSpatialQueryExample(m_world.GetResourceSpatialQueryService(),
                                                     m_world.GetInterestPointProvider());
}
