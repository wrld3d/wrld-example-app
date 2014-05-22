//  Copyright (c) 2014 eeGeo. All rights reserved.

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
