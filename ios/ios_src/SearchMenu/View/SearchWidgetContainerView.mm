
#include "TagCollection.h"
#import "SearchWidgetContainerView.h"


@implementation SearchWidgetContainerView
{
    ExampleApp::SearchMenu::View::SearchWidgetView* m_pInterop;
    
}

- (instancetype)  initWithSearchModel: (WRLDSearchModel*) searchModel
                       searchProvider: (WidgetSearchProvider *) searchProvider
                    navigationEnabled: (BOOL) isNavigationEnabled
                           messageBus: (ExampleApp::ExampleAppMessaging::TMessageBus &) messageBus

{
    self = [super init];
    if (self) {
        m_pInterop = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchWidgetView)(searchModel,
                                                                               searchProvider,
                                                                               searchProvider,
                                                                               isNavigationEnabled,
                                                                               messageBus);
        
        self.frame = [UIScreen mainScreen].bounds;
        self.widget = m_pInterop->GetWidgetView();
        self.speechWidget = m_pInterop->GetSpeechCaptureView();
        
        [self addSubview:self.widget];
        [self addSubview:self.speechWidget];
        
    }
    return self;
}

- (ExampleApp::SearchMenu::View::SearchWidgetView*) getInterop {
    return m_pInterop;
}

- (BOOL) consumesTouch:(UITouch *)touch{
    return [self.widget pointInside:[touch locationInView:self.widget] withEvent:nil] ||
           [self.speechWidget pointInside:[touch locationInView:self.speechWidget] withEvent:nil];
}

-(BOOL) pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    return  [self.widget pointInside:[self convertPoint:point toView:self.widget] withEvent:event] ||
            [self.speechWidget pointInside:[self convertPoint:point toView:self.speechWidget] withEvent:event];
}

@end
