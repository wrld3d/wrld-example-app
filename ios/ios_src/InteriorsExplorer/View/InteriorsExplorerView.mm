// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerView.h"
#include "UIColors.h"
#include "UIHelpers.h"
#include "ImageHelpers.h"
#include "InteriorsExplorerViewInterop.h"
#include "UIHelpers.h"
#include "App.h"
#include "MathFunc.h"
#include "InteriorsExplorerFloorItemView.h"

#import "ImmediatePanGestureRecognizer.h"
#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"
#import <QuartzCore/QuartzCore.h>

namespace
{
    float iPhoneDismissButtonMargin = 28.f;
}

@implementation InteriorsExplorerView

- (ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop*) getInterop
{
    return m_pInterop;
}

- (UIColor*) textColorNormal
{
    return [UIColor colorWithRed:(18.0f/255.0f) green:(86.0f/255.0f) blue:(176.0f/255.0f) alpha:1.0f];
}

- (UIColor*) textColorHighlighted
{
    return [UIColor colorWithRed:(205.0f/255.0f) green:(252.0f/255.0f) blue:(13.0f/255.0f) alpha:1.0f];;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if (self = [super init])
    {
        const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
        
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        
        self.pFloorListViews = [NSMutableArray array];
        
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        m_pInterop = new ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop(self);

        self.frame = CGRectMake(0,
                                0,
                                m_screenWidth,
                                m_screenHeight);
        
        
        m_inactiveFloorListXPosition = m_screenWidth;
        
        const float upperMargin = isPhone ? 20.0f : 50.0f;
        m_inactiveDetailPaneYPosition = m_screenHeight;
        

        self.pFloorPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_inactiveFloorListXPosition, m_screenHeight/2.0f, 120, 200)] autorelease];
        [self addSubview:self.pFloorPanel];
        
        self.pFloorChangeButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 64, 64)] autorelease];
        [self.pFloorChangeButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"floor_selection_button") forState:UIControlStateNormal];
        [self.pFloorChangeButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"floor_selection_button_down") forState:UIControlStateSelected];
        m_draggingFloorButton = NO;
        
        ImmediatePanGestureRecognizer* buttonDrag = [[ImmediatePanGestureRecognizer alloc] initWithTarget:self action:@selector(dragButton:)];
        [self.pFloorChangeButton addGestureRecognizer:buttonDrag];
        [buttonDrag release];

        
        [self.pFloorPanel addSubview:self.pFloorChangeButton];
        
        const float upperPadding = 3.0f;
        self.pFloorOnButtonLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, upperPadding, 64, 64-upperPadding)] autorelease];
        self.pFloorOnButtonLabel.lineBreakMode = NSLineBreakByClipping;
        self.pFloorOnButtonLabel.adjustsFontSizeToFitWidth = NO;
        self.pFloorOnButtonLabel.textColor = [UIColor whiteColor];
        self.pFloorOnButtonLabel.textAlignment = NSTextAlignmentCenter;
        self.pFloorOnButtonLabel.font = [UIFont boldSystemFontOfSize:12.0f];
        self.pFloorOnButtonLabel.userInteractionEnabled = NO;
        [self.pFloorChangeButton addSubview:self.pFloorOnButtonLabel];
        
        
        const float buttonSize = 50.f;
        const float labelLength = isPhone ? fminf(200.f, m_screenWidth*0.5f) : 315.f;
        const float labelSpacing = 11.f;
        
        const float detailsPanelHeight = 50.0f;
        float totalPanelLength = isPhone ? labelLength : labelLength + buttonSize + labelSpacing;
        
        float totalPanelHeight = detailsPanelHeight;
        
        m_detailsPanelHeight = totalPanelHeight;
        
        self.pDetailsPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_screenWidth * 0.5f - totalPanelLength * 0.5f, upperMargin, totalPanelLength, totalPanelHeight)] autorelease];
        
        UIColor* backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        
        const float dismissButtonX = isPhone? m_inactiveFloorListXPosition : totalPanelLength-buttonSize;
        const float dismissButtonY = isPhone? self.pFloorPanel.frame.origin.y - 10.0f : 0.0f;
        UIView* dismissButtonParent = isPhone? self : self.pDetailsPanel;
        self.pDismissButtonBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(backgroundColor)] autorelease];
        self.pDismissButtonBackground.frame = CGRectMake(dismissButtonX, dismissButtonY, buttonSize, buttonSize);
        self.pDismissButtonBackground.userInteractionEnabled = YES;
        [dismissButtonParent addSubview:self.pDismissButtonBackground];
        
        self.pDismissButton = [[[UIButton alloc] initWithFrame:CGRectMake(0.0f, 0.0f, buttonSize, buttonSize)] autorelease];
        [self.pDismissButton setDefaultStatesWithImageNames:@"button_exit_interior_off" :@"button_exit_interior_on"];

        [self.pDismissButton addTarget:self action:@selector(onCancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.pDismissButtonBackground addSubview:self.pDismissButton];
        
        
        self.pDetailsPanelBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(backgroundColor)] autorelease];
        self.pDetailsPanelBackground.frame = CGRectMake(0, 0, labelLength, detailsPanelHeight);
                
        [self.pDetailsPanel addSubview:self.pDetailsPanelBackground];
        
        const float textPadding = 14.f;
        
        self.pFloorNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake( textPadding, textPadding, labelLength - (2*textPadding), detailsPanelHeight - (2*textPadding))] autorelease];
        self.pFloorNameLabel.textColor = [UIColor whiteColor];
        self.pFloorNameLabel.textAlignment = NSTextAlignmentLeft;
        [self.pDetailsPanel addSubview:self.pFloorNameLabel];
                
        
        
        [self addSubview:self.pDetailsPanel];
        
        self.pDetailsPanel.alpha = 0.0f;
        
        m_onScreenParam = 0.f;
        m_touchEnabled = NO;
        m_floorSelectionEnabled = NO;
        
        [self hideFloorLabels];
        [self setHidden:YES];
    }
    
    return self;
}

- (void)layoutSubviews
{
    CGFloat panelHeight = self.pFloorPanel.frame.size.height;
    
    CGRect floorButtonFrame = self.pFloorChangeButton.frame;
    self.pFloorChangeButton.frame = CGRectMake(self.pFloorPanel.frame.size.width*0.5f - floorButtonFrame.size.width*0.5f,
                                               panelHeight - floorButtonFrame.size.height,
                                               floorButtonFrame.size.width,
                                               floorButtonFrame.size.height);
}

- (void)dealloc
{
    delete m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void) show
{
    [self setHidden:NO];
}

- (void) hide
{
    [self setHidden:YES];
}

- (void) onCancelButtonPressed:(UIButton *)sender
{
    m_pInterop->Dismiss();
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    if(!m_touchEnabled)
    {
        return nil;
    }
    
    UIView *hitView = [super hitTest:point withEvent:event];
    if (hitView == self) return nil;
    return hitView;
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    if(!m_touchEnabled)
    {
        return NO;
    }
    
    if(m_floorSelectionEnabled && m_draggingFloorButton)
    {
        return YES;
    }
    
    CGPoint touchLocation = point;
    CGPoint floorPanelLocation = [self convertPoint:touchLocation toView:self.pFloorPanel];
    if (CGRectContainsPoint(self.pFloorChangeButton.frame, floorPanelLocation) && m_floorSelectionEnabled)
        return YES;
    if (CGRectContainsPoint(self.pDetailsPanel.frame, touchLocation))
        return YES;
    if (CGRectContainsPoint(self.pDismissButtonBackground.frame, touchLocation))
        return YES;
    return  NO;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return [self pointInside:touchLocation withEvent:nil];
}

- (void) setFloorName:(const std::string*)name
{
    self.pFloorNameLabel.text = [NSString stringWithUTF8String:name->c_str()];
}

- (void) setSelectedFloor:(int)floorIndex
{
    Eegeo_ASSERT(floorIndex >= 0 && floorIndex < m_tableViewFloorNames.size(), "Invalid floorindex - Out of range 0 << %d << %d", floorIndex, m_tableViewFloorNames.size());
    [self refreshFloorIndicator:floorIndex];
    
    if(!m_draggingFloorButton)
    {
        [self moveButtonToFloorIndex:floorIndex :YES];
    }
}

- (void) updateFloors: (const std::vector<std::string>&) floorShortNames withCurrentFloor: (int) currentlySelectedFloorIndex;
{
    m_tableViewFloorNames = floorShortNames;
    std::reverse(m_tableViewFloorNames.begin(), m_tableViewFloorNames.end());
    
    [self refreshFloorViews];
    
    [self setNeedsLayout];
    [self layoutIfNeeded];
    
    [self refreshFloorIndicator:currentlySelectedFloorIndex];
    [self moveButtonToFloorIndex:currentlySelectedFloorIndex :NO];
}

- (void) refreshFloorViews
{
    for(InteriorsExplorerFloorItemView* item in self.pFloorListViews)
    {
        [item removeFromSuperview];

    }
    
    [self.pFloorListViews removeAllObjects];
    
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    m_floorDivisionHeight = isPhone ? m_screenHeight*0.0625f : 50;
    const float divisionWidth = 30;
    const float divisionLabelWidth = 25;
    const float divisionLabelSpacing = 15;
    float maxHeight = m_screenHeight*0.5f;
    int floorCount = static_cast<int>(m_tableViewFloorNames.size());
    float verticalPadding = ((float)self.pFloorChangeButton.frame.size.height - m_floorDivisionHeight);
    float totalHeight = m_floorDivisionHeight * floorCount + verticalPadding;
    if(totalHeight > maxHeight)
    {
        m_floorDivisionHeight = (maxHeight-verticalPadding)/(floorCount);
        totalHeight = maxHeight;
        verticalPadding = ((float)self.pFloorChangeButton.frame.size.height - m_floorDivisionHeight);
    }
    
    CGRect floorPanelFrame = self.pFloorPanel.frame;
    const float floorPanelVerticalCenterline = isPhone ? 0.54f : 0.5f;
    floorPanelFrame.origin.y = m_screenHeight*floorPanelVerticalCenterline - totalHeight*0.5f;
    floorPanelFrame.size.height = totalHeight;
    self.pFloorPanel.frame = floorPanelFrame;
    
    if(isPhone)
    {
        CGRect dismissButtonFrame = self.pDismissButtonBackground.frame;
        const float dismissButtonSpacing = 10.f;
        dismissButtonFrame.origin.y = (self.pFloorPanel.frame.origin.y - dismissButtonSpacing) - dismissButtonFrame.size.height;
        self.pDismissButtonBackground.frame = dismissButtonFrame;
    }
    
    float yOffset = ((float)self.pFloorChangeButton.frame.size.height - m_floorDivisionHeight)*0.5f;
    int floorIndex = 0;
    for(std::vector<std::string>::const_iterator it = m_tableViewFloorNames.begin(); it != m_tableViewFloorNames.end(); it++)
    {
        const std::string& name = *it;
        NSString* nameString = [NSString stringWithCString:name.c_str() encoding:NSUTF8StringEncoding];
        
        InteriorsExplorerFloorItemView* pFloorView = [[[InteriorsExplorerFloorItemView alloc] initWithParams:divisionLabelWidth
                                                                                                            :divisionLabelSpacing
                                                                                                            :divisionWidth
                                                                                                            :m_floorDivisionHeight
                                                                                                            :m_pixelScale
                                                                                                            :nameString
                                                                                                            :(floorIndex == 0)
                                                                                                            :(floorIndex == floorCount-1)] autorelease];
        CGRect viewFrame = pFloorView.frame;
        viewFrame.origin.y = yOffset;
        viewFrame.origin.x = (self.pFloorPanel.frame.size.width*0.5f) - ((divisionLabelWidth + divisionLabelSpacing) + 0.5 * divisionWidth);
        pFloorView.frame = viewFrame;
        
        [self.pFloorPanel insertSubview:pFloorView belowSubview:self.pFloorChangeButton];
        [self.pFloorListViews addObject:pFloorView];
        
        yOffset += m_floorDivisionHeight;
        floorIndex++;
    }
    
    m_floorSelectionEnabled= (floorCount > 1);
    self.pFloorPanel.hidden = !m_floorSelectionEnabled;
    self.pFloorPanel.userInteractionEnabled = self.pFloorChangeButton.userInteractionEnabled = m_floorSelectionEnabled;
}

- (void) refreshFloorIndicator:(int)floorIndex
{
    int nameIndex = static_cast<int>(m_tableViewFloorNames.size()-1) - floorIndex;
    self.pFloorOnButtonLabel.text = [NSString stringWithCString:m_tableViewFloorNames.at(nameIndex).c_str() encoding:NSUTF8StringEncoding];
}

- (float) GetXPositionForFloorPanelAt:(float)t
{
    float openX = iPhoneDismissButtonMargin + (0.5f * self.pDismissButtonBackground.frame.size.width + 0.5f * self.pFloorPanel.frame.size.width);
    return m_screenWidth - t * openX;
}

- (float) GetXPositionForDismissButtonAt:(float)t
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    return isPhone ? m_screenWidth - t * (iPhoneDismissButtonMargin + self.pDismissButtonBackground.frame.size.width) : 0.0f;
}

- (void) setFullyOnScreen
{
    [self animateTo:1.0f];
}

- (void) setFullyOffScreen
{
    [self animateTo:0.0f];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    
    CGRect floorPanel = self.pFloorPanel.frame;
    floorPanel.origin.x = [self GetXPositionForFloorPanelAt :onScreenState];
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    if(isPhone)
    {
        CGRect dismissPanel = self.pDismissButtonBackground.frame;
        dismissPanel.origin.x = [self GetXPositionForDismissButtonAt:onScreenState];
        
        self.pDismissButtonBackground.frame = dismissPanel;
    }
    
    self.hidden = onScreenState == 0.0f;
    self.pFloorPanel.frame = floorPanel;
    
    self.pDetailsPanel.alpha = onScreenState;
    m_onScreenParam = onScreenState;
}

- (void) animateTo:(float)t
{
    CGRect floorFrame = self.pFloorPanel.frame;
    floorFrame.origin.x = [self GetXPositionForFloorPanelAt:t];
    
    CGRect dismissButtonFrame = self.pDismissButtonBackground.frame;
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    if(isPhone)
    {
        dismissButtonFrame.origin.x = [self GetXPositionForDismissButtonAt:t];
    }
    
    if(t > 0.f)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                          delay:0.0f
                        options:UIViewAnimationOptionBeginFromCurrentState
                     animations:^
     {
         self.pFloorPanel.frame = floorFrame;
         self.pDetailsPanel.alpha = t;
         if(isPhone)
         {
             self.pDismissButtonBackground.frame = dismissButtonFrame;
         }
     }
                     completion:^(BOOL finished)
     {
         self.hidden = (t == 0.0f);
         m_onScreenParam = t;
     }
     ];
}

- (void) setTouchEnabled:(BOOL)enabled
{
    m_touchEnabled = enabled;
}

- (void) dragButton:(ImmediatePanGestureRecognizer*)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateChanged ||
       recognizer.state == UIGestureRecognizerStateEnded)
    {
        
        CGPoint translation = [recognizer translationInView:self.pFloorChangeButton];
        CGRect buttonFrame = self.pFloorChangeButton.frame;
        buttonFrame.origin.y += translation.y;
        buttonFrame.origin.y = Eegeo::Clamp((float)buttonFrame.origin.y, 0.0f, (float)(self.pFloorPanel.frame.size.height-buttonFrame.size.height));
        self.pFloorChangeButton.frame = buttonFrame;
        
        [recognizer setTranslation:CGPointZero inView:self.pFloorChangeButton];
    }
    
    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        [self showFloorLabels];
    }
    
    m_draggingFloorButton = recognizer.state != UIGestureRecognizerStateEnded &&
                            recognizer.state != UIGestureRecognizerStateFailed &&
                            recognizer.state != UIGestureRecognizerStateCancelled;
    m_floorButtonParameter = 1.0f - (float)(self.pFloorChangeButton.frame.origin.y / (self.pFloorPanel.frame.size.height-self.pFloorChangeButton.frame.size.height));
    
    if(m_draggingFloorButton)
    {
        m_pInterop->SetFloorSelectionDrag(m_floorButtonParameter);
        [self.pFloorChangeButton setSelected:YES];
    }
    else
    {
        int floorCount = (int)m_tableViewFloorNames.size()-1;
        int floorIndex = (int)roundf(m_floorButtonParameter*floorCount);
        m_pInterop->SelectFloor(floorIndex);
        
        [self moveButtonToFloorIndex:floorIndex :YES];
        [self.pFloorChangeButton setSelected:NO];
        [self hideFloorLabels];
    }
}

- (void) hideFloorLabels
{
    for(InteriorsExplorerFloorItemView* item in self.pFloorListViews)
    {
        [item hideName];
    }
    
    self.pFloorOnButtonLabel.textColor = [self textColorNormal];
}

- (void) showFloorLabels
{
    for(InteriorsExplorerFloorItemView* item in self.pFloorListViews)
    {
        [item showName];
    }
    
    self.pFloorOnButtonLabel.textColor = [self textColorHighlighted];
}

- (void) moveButtonToFloorIndex:(int)floorIndex :(BOOL)shouldAnimate
{
    int floorCount = static_cast<int>(self.pFloorListViews.count);
    InteriorsExplorerFloorItemView* topItem = [self.pFloorListViews objectAtIndex:0];
    CGRect topFrame = topItem.frame;
    CGFloat topY = topFrame.origin.y + (m_floorDivisionHeight*0.5f) - self.pFloorChangeButton.frame.size.height*0.5f;
    CGFloat newY = topY + ((floorCount-1)-floorIndex) * m_floorDivisionHeight;
    
    if(shouldAnimate)
    {
        [UIView animateWithDuration:0.25
                              delay:0
                            options:UIViewAnimationOptionBeginFromCurrentState
                         animations:^(void){
                             CGRect buttonFrame = self.pFloorChangeButton.frame;
                             buttonFrame.origin.y = newY;
                             self.pFloorChangeButton.frame = buttonFrame;
            
        }
                         completion:^(BOOL finished){
            
        }];
    }
    else
    {
        CGRect buttonFrame = self.pFloorChangeButton.frame;
        buttonFrame.origin.y = newY;
        self.pFloorChangeButton.frame = buttonFrame;
    }
}

@end

