//
//  IExampleFactory.h
//  ExampleApp
//
//  Created by Scott on 21/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef ExampleApp_IExampleFactory_h
#define ExampleApp_IExampleFactory_h

#include "IExample.h"
#include <string>

namespace Examples
{
class IExampleFactory
{
public:
	virtual ~IExampleFactory() { }

	virtual std::string ExampleName() const = 0;
	virtual IExample* CreateExample() const = 0;
};
}

#endif
