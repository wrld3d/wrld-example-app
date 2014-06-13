// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef IANDROIDTOUCHINPUTHANDLER_H_
#define IANDROIDTOUCHINPUTHANDLER_H_

#include "TouchEventWrapper.h"

class IAndroidTouchInputHandler
{
public:
	virtual ~IAndroidTouchInputHandler() {};
	virtual void HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event) = 0;
};

#endif /* IANDROIDTOUCHINPUTHANDLER_H_ */
