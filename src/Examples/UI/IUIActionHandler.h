// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ExampleApp_IUIActionHandler_h
#define ExampleApp_IUIActionHandler_h

namespace Examples
{
class IUIActionHandler
{
public:
	virtual ~IUIActionHandler() {}
	virtual void operator()() = 0;
};
}

#endif
