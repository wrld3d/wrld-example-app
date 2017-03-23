// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#import <CoreFoundation/CFMessagePort.h>
#import <CoreFoundation/CFRunLoop.h>
#import <XCTest/XCTest.h>
#import "FastlaneUITest-Swift.h"

extern "C" CFDataRef MessageCallback(CFMessagePortRef local, SInt32 msgId, CFDataRef data, void *ctx);

class FastlaneMachServer
{
public:
    FastlaneMachServer()
    : m_context((CFMessagePortContext) {0, this, NULL, NULL})
    , m_port(CFMessagePortCreateLocal(kCFAllocatorDefault, CFSTR("com.eegeo.mobileexampleapp.group.fastlane.port"), &MessageCallback, &m_context, NULL))
    , m_runLoopSource(CFMessagePortCreateRunLoopSource(kCFAllocatorDefault, m_port, 0))
    {
        CFRunLoopAddSource(CFRunLoopGetCurrent(), m_runLoopSource, kCFRunLoopCommonModes);
        CFMessagePortSetDispatchQueue(m_port, dispatch_get_main_queue());
    }

    ~FastlaneMachServer()
    {
        CFRunLoopRemoveSource(CFRunLoopGetCurrent(), m_runLoopSource, kCFRunLoopCommonModes);
        CFRelease(m_runLoopSource);
        CFRelease(m_port);
    }

    void OnMessageReceived(SInt32 msgId, CFDataRef data)
    {
        switch (msgId)
        {
        //case TakeScreenshotMessageId:
        case 1: {
            NSString* filename = [[NSString alloc] initWithData:(NSData*)data encoding:NSUTF8StringEncoding];
            [Snapshot snapshot:filename waitForLoadingIndicator:YES];
        } break;

        //case ScreenshotsCompleteMessageId:
        case 2: {
        } break;

        default: {
            ;
        }
        }
    }
    
private:
    CFMessagePortContext m_context;
    CFMessagePortRef m_port;
    CFRunLoopSourceRef m_runLoopSource;
};


extern "C" CFDataRef MessageCallback(CFMessagePortRef local, SInt32 msgId, CFDataRef data, void *ctx)
{
    ((FastlaneMachServer*) ctx)->OnMessageReceived(msgId, data);
    return NULL;
}


@interface UITests : XCTestCase
{
    FastlaneMachServer m_messageServer;
}
@end

@implementation UITests

- (void)setUp {
    [super setUp];
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    // In UI tests it is usually best to stop immediately when a failure occurs.
    self.continueAfterFailure = NO;
    // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
    
    // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [Snapshot setupSnapshot:app];
    [app launch];
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // Use recording to get started writing UI tests.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
}

@end
