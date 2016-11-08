// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "MobileExampleApp.h"

class AppUrlDelegate;

@interface AppUrlDelegateOpenListener : NSObject

-(void) registerForOpenUrlNotifications:(AppUrlDelegate*)pAppUrlDelegate;

@end

class AppUrlDelegate : protected Eegeo::NonCopyable
{
public:
    AppUrlDelegate(ExampleApp::MobileExampleApp& exampleApp);
    ~AppUrlDelegate();
    
    void Event_OpenUrl(const AppInterface::UrlData& data);
    
private:
    ExampleApp::MobileExampleApp& m_exampleApp;
    AppUrlDelegateOpenListener* m_pAppUrlDelegateOpenListener;
};
