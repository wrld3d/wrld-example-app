// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InteriorsExplorerViewIncludes.h"
#include "InteriorsExplorerTutorialView.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include <string>
#include <vector>

template <typename Context, typename T0>
class TObjCCallback1 : public Eegeo::Helpers::ICallback1<T0> {
public:
    typedef void (*TCallbackTarget)(id, SEL, T0);
    
    TObjCCallback1() {}
    
    void SetupCallback(Context *context, SEL selector)
    {
        m_context = context;
        m_selector = selector;
        m_callback = (TCallbackTarget)[m_context methodForSelector:selector];
    }
    
    void operator()(T0& arg0) const
    {
        m_callback(m_context, m_selector, arg0);
    }
    
private:
    Context *m_context;
    SEL m_selector;
    TCallbackTarget m_callback;
};

@class InteriorsExplorerView;

@interface InteriorsExplorerView : UIView<UITableViewDataSource, UITableViewDelegate>
{
    ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop* m_pInterop;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_inactiveFloorListXPosition;
    float m_inactiveDetailPaneYPosition;
    
    float m_onScreenParam;
    float m_stateChangeAnimationTimeSeconds;
    
    float m_detailsPanelHeight;
    float m_floorDivisionHeight;
    float m_halfButtonHeight;
    float m_halfDivisionHeight;
    BOOL m_touchEnabled;
    BOOL m_draggingFloorButton;
    BOOL m_floorSelectionEnabled;
    float m_floorButtonParameter;
    float m_floorSelection;
    BOOL m_isSliderAnimPlaying;
    
    CGRect m_scrollRect;
    
    std::vector<std::string> m_tableViewFloorNames;
    
    TObjCCallback1<InteriorsExplorerView, const ExampleApp::AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
    
    ExampleApp::ExampleAppMessaging::TMessageBus* m_messageBus;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale :(ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus :(InteriorsExplorerTutorialView&)tutorialView;

- (ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) show;

- (void) hide;

- (void) setFloorName:(const std::string*)name;

- (void) setSelectedFloor:(int)floorIndex;

- (void) updateFloors: (const std::vector<std::string>&) floorNumbers withCurrentFloor: (int) currentlySelectedFloor;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateTo:(float)t;

- (void) setTouchEnabled:(BOOL)enabled;

- (void) refreshFloorViews;

- (void) playSliderShakeAnim;

- (bool) GetCanShowChangeFloorTutorialDialog;

- (void) onAppModeChanged:(const ExampleApp::AppModes::AppModeChangedMessage&)appMode;

// NOTE: Replace these once integrated with search ux colour scheme.
- (UIColor*) textColorNormal;
- (UIColor*) textColorHighlighted;

@property(nonatomic, retain) UIView* pFloorPanel;
@property(nonatomic, retain) UIButton* pFloorChangeButton;
@property(nonatomic, retain) UILabel* pFloorOnButtonLabel;

@property(nonatomic, retain) UIView* pDetailsPanel;
@property(nonatomic, retain) UIImageView* pDetailsPanelBackground;
@property(nonatomic, retain) UIImageView* pDetailsPanelRight;

@property(nonatomic, retain) UIButton* pDismissButton;
@property(nonatomic, retain) UIImageView* pDismissButtonBackground;
@property(nonatomic, retain) UILabel* pFloorNameLabel;

@property(nonatomic, retain) UITableView* pFloorListView;
@property(nonatomic, retain) UIImageView* pFloorListArrowUp;
@property(nonatomic, retain) UIImageView* pFloorListArrowDown;

@property(nonatomic, retain) InteriorsExplorerTutorialView* pTutorialView;
@property(nonatomic, retain) NSTimer* pTimer;

@end