// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
