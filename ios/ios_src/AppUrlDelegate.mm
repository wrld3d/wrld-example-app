// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppUrlDelegate.h"

@implementation AppUrlDelegateOpenListener

AppUrlDelegate* m_pAppUrlDelegate;

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter]removeObserver: self
     name: @"handleOpenUrl"
     object: nil];
    
    [super dealloc];
}

-(void) registerForOpenUrlNotifications:(AppUrlDelegate*)pAppUrlDelegate
{
    m_pAppUrlDelegate = pAppUrlDelegate;
    
    [[NSNotificationCenter defaultCenter] addObserver: self
        selector: @selector(onOpenUrl:)
        name: @"handleOpenUrl"
        object: nil];
}

- (void)onOpenUrl:(NSNotification *)notification
{
    NSURL* url = [notification object];
    
    AppInterface::UrlData data;
    data.host = [url.host UTF8String];
    data.path = [url.path UTF8String];
    data.query = [url.query UTF8String];
    m_pAppUrlDelegate->Event_OpenUrl(data);
}

@end

AppUrlDelegate::AppUrlDelegate(ExampleApp::MobileExampleApp& exampleApp)
    :m_exampleApp(exampleApp)
{
    m_pAppUrlDelegateOpenListener = [[AppUrlDelegateOpenListener alloc] init];
    [m_pAppUrlDelegateOpenListener registerForOpenUrlNotifications:this];
}

AppUrlDelegate::~AppUrlDelegate()
{
    [m_pAppUrlDelegateOpenListener release];
    m_pAppUrlDelegateOpenListener = nil;
}

void AppUrlDelegate::Event_OpenUrl(const AppInterface::UrlData& data)
{
    m_exampleApp.Event_OpenUrl(data);
}

