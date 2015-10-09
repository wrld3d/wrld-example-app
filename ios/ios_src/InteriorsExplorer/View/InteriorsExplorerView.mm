// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "InteriorsExplorerViewInterop.h"
#include "App.h"

#import "UIView+TouchExclusivity.h"

@implementation InteriorsExplorerView

- (ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop*) getInterop
{
    return m_pInterop;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if (self = [super init])
    {
        const bool isPhone = App::IsDeviceSmall();
        
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        m_pInterop = new ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop(self);

        self.frame = CGRectMake(0,
                                0,
                                m_screenWidth,
                                m_screenHeight);
        
        
        m_inactiveFloorListXPosition = -50.f;
        
        const float upperMargin = 50.0f;
        m_inactiveDetailPaneYPosition = m_screenHeight;
        
        self.pFloorPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_inactiveFloorListXPosition, m_screenHeight/2.0f, 50, 200)] autorelease];
        [self addSubview:self.pFloorPanel];
        
        self.pFloorPanelTop = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"floor_selection_top")] autorelease];
        self.pFloorPanelBottom = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"floor_selection_bottom")] autorelease];
        self.pFloorList = [[[UITableView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) style:UITableViewStylePlain] autorelease];
        self.pFloorList.delegate = self;
        self.pFloorList.dataSource = self;
        [self.pFloorPanel addSubview:self.pFloorPanelTop];
        [self.pFloorPanel addSubview:self.pFloorList];
        [self.pFloorPanel addSubview:self.pFloorPanelBottom];
        
        const float buttonSize = 40.f;
        const float labelLength = isPhone? 150.f : 200.f;
        
        const float detailsPanelHeight = 40.0f;
        float totalPanelLength = labelLength + buttonSize;
        
        float totalPanelHeight = detailsPanelHeight;
        
        m_detailsPanelHeight = totalPanelHeight;
        
        self.pDetailsPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_screenWidth * 0.5f - totalPanelLength * 0.5f, upperMargin, totalPanelLength, totalPanelHeight)] autorelease];
        
        
        self.pDismissButtonBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"menu_button")] autorelease];
        self.pDismissButtonBackground.frame = CGRectMake(0.0f, 0.0f, buttonSize, buttonSize);
        
        [self.pDetailsPanel addSubview:self.pDismissButtonBackground];
        
        self.pDismissButton = [[[UIButton alloc] initWithFrame:CGRectMake(0.0f, 0.0f, buttonSize, buttonSize)] autorelease];
        [self.pDismissButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"Arrow") forState:UIControlStateNormal];
        [self.pDismissButton addTarget:self action:@selector(onCancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.pDismissButtonBackground addSubview:self.pDismissButton];
        
        self.pDismissButtonBackground.userInteractionEnabled = YES;
        
        self.pDetailsPanelBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"place_pin_background")] autorelease];
        
        self.pDetailsPanelBackground.frame = CGRectMake(buttonSize, 0, labelLength, detailsPanelHeight);
        
        UIBezierPath* roundedShapePath = [UIBezierPath bezierPathWithRoundedRect:self.pDetailsPanelBackground.bounds byRoundingCorners:UIRectCornerTopRight | UIRectCornerBottomRight cornerRadii:CGSizeMake(7.0f, 7.0f)];
        
        CAShapeLayer* roundedShapeLayer = [CAShapeLayer layer];
        roundedShapeLayer.frame = self.pDetailsPanelBackground.bounds;
        roundedShapeLayer.path = roundedShapePath.CGPath;
        roundedShapeLayer.fillColor = [UIColor blackColor].CGColor;
        roundedShapeLayer.strokeColor = [UIColor blackColor].CGColor;
        roundedShapeLayer.lineWidth = 1.0f;
        
        self.pDetailsPanelBackground.layer.mask = roundedShapeLayer;
        
        [self.pDetailsPanel addSubview:self.pDetailsPanelBackground];
        
        const float textPadding = 2.f;
        
        self.pFloorNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake( textPadding + buttonSize, textPadding, labelLength - textPadding, detailsPanelHeight - textPadding)] autorelease];
        self.pFloorNameLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pFloorNameLabel.textAlignment = NSTextAlignmentCenter;
        [self.pDetailsPanel addSubview:self.pFloorNameLabel];
        
        
        [self addSubview:self.pDetailsPanel];
        
        m_onScreenParam = 0.f;
        m_touchEnabled = NO;
        
        [self setHidden:YES];
    }
    
    return self;
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

- (void)layoutSubviews
{
    const int borderHeight = 20;
    const int floorPanelWidth = 50;
    CGFloat listHeight = self.pFloorList.contentSize.height;
    CGFloat totalFloorPanelHeight = (borderHeight * 2.f) + listHeight;
    
    CGRect originalFloorPanelFrame = self.pFloorPanel.frame;
    CGFloat newY = m_screenHeight/2.0f - totalFloorPanelHeight/2.0f;
    originalFloorPanelFrame.origin.y = newY;
    originalFloorPanelFrame.size.height = totalFloorPanelHeight;
    
    self.pFloorPanel.frame = originalFloorPanelFrame;
    self.pFloorPanelTop.frame = CGRectMake(0, 0, floorPanelWidth, borderHeight);
    self.pFloorList.frame = CGRectMake(0, borderHeight, floorPanelWidth, listHeight);
    self.pFloorPanelBottom.frame = CGRectMake(0, borderHeight+listHeight-1, floorPanelWidth, borderHeight);
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

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(!m_touchEnabled)
    {
        return NO;
    }
    
    CGPoint touchLocation = [touch locationInView:self];
    if (CGRectContainsPoint(self.pFloorPanel.frame, touchLocation))
        return YES;
    if (CGRectContainsPoint(self.pDetailsPanel.frame, touchLocation))
        return YES;
    return  NO;
}

- (void) setFloorName:(const std::string*)name;
{
    self.pFloorNameLabel.text = [NSString stringWithUTF8String:name->c_str()];
}

- (void) updateFloors: (const std::vector<std::string>&) floorShortNames withCurrentFloor: (int) currentlySelectedFloorIndex;
{
    m_tableViewFloorNames = floorShortNames;
    std::reverse(m_tableViewFloorNames.begin(), m_tableViewFloorNames.end());
    
    [self.pFloorList reloadData];
    int rowIndex = [self reverseIndex:currentlySelectedFloorIndex];
    [self.pFloorList selectRowAtIndexPath:[NSIndexPath indexPathForRow:rowIndex inSection:0] animated:NO scrollPosition:static_cast<UITableViewScrollPosition>(0)];
    [self.pFloorList sizeToFit];
    [self layoutIfNeeded];
    [self setNeedsLayout];
}

- (int) reverseIndex:(int)floorIndex
{
    return int((m_tableViewFloorNames.size() - floorIndex)-1);
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return m_tableViewFloorNames.size();
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    return nil;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 0.0f;
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *Identifier = @"ReusableCellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:Identifier];
    if(cell == nil)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:Identifier];
        cell.textLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        cell.backgroundView = [[UIImageView alloc] initWithImage:[ [UIImage imageNamed:@"place_pin_background"] stretchableImageWithLeftCapWidth:0.0 topCapHeight:0.0] ];
        UIView *selectedColorView = [[UIView alloc] init];
        selectedColorView.backgroundColor = ExampleApp::Helpers::ColorPalette::LightGreyTone;
        [cell setSelectedBackgroundView:selectedColorView];
    }
    
    cell.textLabel.text = [NSString stringWithUTF8String:m_tableViewFloorNames.at(indexPath.item).c_str()];
    
    return cell;
}



- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    m_pInterop->SelectFloor([self reverseIndex:static_cast<int>(indexPath.item)]);
}

- (void) setFullyOnScreen
{
    if(m_onScreenParam == 1.0f)
    {
        return;
    }
    
    [self animateTo:1.0f];
}

- (void) setFullyOffScreen
{
    if(m_onScreenParam == 0.0f)
    {
        return;
    }
    
    [self animateTo:0.0f];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newX = -50 + onScreenState * 50;
    
    CGRect floorPanel = self.pFloorPanel.frame;
    floorPanel.origin.x = newX;
    
    self.hidden = onScreenState == 0.0f;
    self.pFloorPanel.frame = floorPanel;
    
    self.pDetailsPanel.alpha = onScreenState;
    m_onScreenParam = onScreenState;
    
    self.pDismissButton.alpha = onScreenState;
}

- (void) animateTo:(float)t
{
    float newX = -50 + t * 50;
    
    CGRect floorFrame = self.pFloorPanel.frame;
    floorFrame.origin.x = newX;
    
    if(t > 0.f)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.pFloorPanel.frame = floorFrame;
         self.pDetailsPanel.alpha = t;
         self.pDismissButton.alpha = t;
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

@end