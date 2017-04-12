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

namespace
{
    typedef ExampleApp::ApplicationConfig::ApplicationConfiguration ApplicationConfiguration;
    
    ApplicationConfiguration LoadConfiguration()
    {
        // create file IO instance (iOSPlatformAbstractionModule not yet available in app lifetime)
        Eegeo::iOS::iOSFileIO tempFileIO;
        
        ExampleApp::ApplicationConfig::SdkModel::iOSApplicationConfigurationVersionProvider iOSVersionProvider;
        
        return ExampleApp::ApplicationConfig::SdkModel::LoadAppConfig(tempFileIO, iOSVersionProvider, ExampleApp::ApplicationConfigurationPath);
    }
}



@implementation AppDelegate

@synthesize window = _window;

-(void) dealloc
{
    Eegeo_DELETE _metricsService;
    Eegeo_DELETE _applicationConfiguration;
    
    [super dealloc];
}


-(BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    _metricsService = Eegeo_NEW(ExampleApp::Metrics::iOSFlurryMetricsService)();
    
    const ApplicationConfiguration& appConfig = LoadConfiguration();
    _applicationConfiguration = Eegeo_NEW(ApplicationConfiguration)(appConfig);
    
    // Flurry metrics service must be started during didFinishLaunchingWithOptions (events not logged on >= iOS 8.0 if started later)
    _metricsService->BeginSession(_applicationConfiguration->FlurryAppKey(), appConfig.CombinedVersionString());
    
    NSString *hockeyAppId = [NSString stringWithCString:appConfig.HockeyAppId().c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    [[BITHockeyManager sharedHockeyManager] configureWithIdentifier:hockeyAppId];
    // Do some additional configuration if needed here
    [BITHockeyManager sharedHockeyManager].logLevel = BITLogLevelDebug;
    [[BITHockeyManager sharedHockeyManager].crashManager setCrashManagerStatus: BITCrashManagerStatusAutoSend];
    [[BITHockeyManager sharedHockeyManager] startManager];
    [[BITHockeyManager sharedHockeyManager].authenticator
     authenticateInstallation];
    
    if(launchOptions[@"UIApplicationLaunchOptionsURLKey"])
    {
        NSURL *url = launchOptions[@"UIApplicationLaunchOptionsURLKey"];
        _launchUrl = url;
    }
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


@end
