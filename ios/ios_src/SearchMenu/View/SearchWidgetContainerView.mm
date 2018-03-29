//
//  SearchWidgetView.m
//  ProjectSwallowApp
//
//  Created by David Crooks on 28/03/2018.
//

#include "TagCollection.h"
#import "SearchWidgetContainerView.h"


@implementation SearchWidgetContainerView
{
    ExampleApp::SearchMenu::View::SearchWidgetView* m_pInterop;
    
}

- (instancetype)initWithSearchProvider:(WidgetSearchProvider *) searchProvider
                            messageBus:(ExampleApp::ExampleAppMessaging::TMessageBus &) messageBus

{
    self = [super init];
    if (self) {
        m_pInterop = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchWidgetView)(searchProvider,
                                                                 searchProvider,
                                                                 messageBus);
        
        self.frame = [UIScreen mainScreen].bounds;
        self.widget = m_pInterop->GetWidgetView();
        
        [self addSubview:self.widget];
        
    }
    return self;
}

- (ExampleApp::SearchMenu::View::SearchWidgetView*) getInterop {
    return m_pInterop;
}

- (BOOL) consumesTouch:(UITouch *)touch{
    return [self.widget pointInside:[touch locationInView:self.widget] withEvent:nil];
}

-(BOOL) pointInside:(CGPoint)point withEvent:(UIEvent *)event {
    return [self.widget pointInside:[self convertPoint:point toView:self.widget] withEvent:event];
}

@end
