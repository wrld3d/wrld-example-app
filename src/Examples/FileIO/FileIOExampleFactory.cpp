//
//  FileIOExampleFactory.cpp
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "FileIOExampleFactory.h"
#include "FileIOExample.h"

using namespace Examples;

FileIOExampleFactory::FileIOExampleFactory(Eegeo::EegeoWorld& world)
: m_world(world)
{
    
}

IExample* FileIOExampleFactory::CreateExample() const
{
    return new Examples::FileIOExample(m_world.GetFileIO());
}

std::string FileIOExampleFactory::ExampleName() const
{
	return Examples::FileIOExample::GetName();
}


