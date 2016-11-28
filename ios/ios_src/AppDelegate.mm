// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "AppDelegate.h"
#include "Flurry.h"
#include "ViewController.h"

#include "ApiKey.h"
#include "iOSApplicationConfigurationVersionProvider.h"
#include "iOSFileIO.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"
#include "iOSFlurryMetricsService.h"
#include "DeepLinkModule.h"
#include "AppInterface.h"
#include "DeepLinkConfigHandler.h"

@implementation AppDelegate

@synthesize window = _window;

-(void) dealloc
{
    Eegeo_DELETE _metricsService;
    Eegeo_DELETE _applicationConfiguration;
    Eegeo_DELETE _pIOSVersionProvider;
    
    [super dealloc];
}


-(BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSString* DeepLinkOptionsKey = @"UIApplicationLaunchOptionsURLKey";
    // Override point for customization after application launch.
    _metricsService = Eegeo_NEW(ExampleApp::Metrics::iOSFlurryMetricsService)();
    
    NSURL* appConfigDeepLinkUrl = nil;
    if(launchOptions[DeepLinkOptionsKey])
    {
        NSURL *url = launchOptions[DeepLinkOptionsKey];
        
        if([[url host] isEqualToString:[NSString stringWithUTF8String:ExampleApp::DeepLink::SdkModel::MYMAP_PATH]])
        {
            appConfigDeepLinkUrl = url;
        }
        else
        {
            _launchUrl = url;
        }
    }

    [self LoadAppConfig:appConfigDeepLinkUrl];
    
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    
    [[NSNotificationCenter defaultCenter] postNotificationName: @"handlePause"
                                                        object: nil
                                                      userInfo: nil];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    
    [[NSNotificationCenter defaultCenter] postNotificationName: @"handleResume"
                                                        object: nil
                                                      userInfo: nil];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    
    [UIApplication sharedApplication].delegate = nil;
}



- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    [[NSNotificationCenter defaultCenter] postNotificationName: @"handleOpenUrl"
                                                        object: url
                                                      userInfo: nil];
    return YES;
}

- (void) LoadAppConfig:(NSURL*) deepLinkUrl
{
    _pIOSVersionProvider = Eegeo_NEW(ExampleApp::ApplicationConfig::SdkModel::iOSApplicationConfigurationVersionProvider)();
    
    if(deepLinkUrl != nil)
    {
        AppInterface::UrlData deepLinkData = {[[deepLinkUrl host] UTF8String], [[deepLinkUrl path] UTF8String]};
        
        NSString* url = [NSString stringWithUTF8String:ExampleApp::DeepLink::SdkModel::GenerateConfigUrl(deepLinkData).c_str()];
        NSURL* configWebRequestUrl= [NSURL URLWithString:url];
        NSURLRequest *request = [NSURLRequest requestWithURL:configWebRequestUrl cachePolicy:NSURLRequestReturnCacheDataElseLoad timeoutInterval:30.0];
        [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *response, NSData *data, NSError *error)
         {
             if (error)
             {
                 Eegeo_TTY("Error loading application config from web, reverting to default.");
                 Eegeo::iOS::iOSFileIO tempFileIO;
                 
                 [self OnLoadAppConfig: ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(tempFileIO, *_pIOSVersionProvider, ExampleApp::ApplicationConfigurationPath)];
             }
             else
             {
                 const NSString* configResult = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
                 
                 ExampleApp::ApplicationConfig::ApplicationConfiguration* pAppConfig = ExampleApp::ApplicationConfig::SdkModel::CreateConfigFromJson([configResult UTF8String], *_pIOSVersionProvider);
                 if(pAppConfig != NULL)
                 {
                     ExampleApp::ApplicationConfig::ApplicationConfiguration returnConfig(*pAppConfig);
                     Eegeo_DELETE(pAppConfig);
                     [self OnLoadAppConfig: returnConfig];
                 }
                 else
                 {
                     // create file IO instance (iOSPlatformAbstractionModule not yet available in app lifetime)
                     Eegeo::iOS::iOSFileIO tempFileIO;
                     [self OnLoadAppConfig: ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(tempFileIO, *_pIOSVersionProvider, ExampleApp::ApplicationConfigurationPath)];
                 }
                 [configResult release];
             }
         }];
    }
    else
    {
        // create file IO instance (iOSPlatformAbstractionModule not yet available in app lifetime)
        Eegeo::iOS::iOSFileIO tempFileIO;
        [self OnLoadAppConfig: ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(tempFileIO, *_pIOSVersionProvider, ExampleApp::ApplicationConfigurationPath)];
    }
}
- (void) OnLoadAppConfig:(const ExampleApp::ApplicationConfig::ApplicationConfiguration&) appConfig
{
    _applicationConfiguration = Eegeo_NEW(ExampleApp::ApplicationConfig::ApplicationConfiguration)(appConfig);
    [[NSNotificationCenter defaultCenter] postNotificationName:@"handleConfigLoad"
                                                        object:nil];
    // Flurry metrics service must be started during didFinishLaunchingWithOptions (events not logged on >= iOS 8.0 if started later)
    _metricsService->BeginSession(_applicationConfiguration->FlurryAppKey(), appConfig.CombinedVersionString());
}


@end
