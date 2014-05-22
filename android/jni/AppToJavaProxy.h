//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IAPPTOJAVAPROXY_H_
#define IAPPTOJAVAPROXY_H_

#include "AppToJavaHandler.h"
#include "Types.h"
#include "LatLongAltitude.h"

// Calls to this proxy are handled in AppToJavaHandler within the
// context of the 'Android Main (UI)' thread
// Therefore, it is only safe to pass simple immutable data via this proxy
// It is not safe to make cross-thread calls into types exposed via AppProxy/AppRunner.
class AppToJavaProxy : protected Eegeo::NonCopyable
{
public:
	AppToJavaProxy(AppToJavaHandler& appToJavaHandler);

private:
	AppToJavaHandler& m_appToJavaHandler;
};

#endif
