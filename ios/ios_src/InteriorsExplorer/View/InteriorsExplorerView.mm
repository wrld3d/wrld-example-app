// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "InteriorsExplorerViewInterop.h"
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
        m_inactiveDetailPaneYPosition = m_screenHeight;
        
        self.pFloorPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_inactiveFloorListXPosition, m_screenHeight/2.0f, 50, 200)] autorelease];
        [self addSubview:self.pFloorPanel];

        m_floorCount = 0;
        
        self.pFloorPanelTop = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"floor_selection_top")] autorelease];
        self.pFloorPanelBottom = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"floor_selection_bottom")] autorelease];
        self.pFloorList = [[[UITableView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) style:UITableViewStylePlain] autorelease];
        self.pFloorList.delegate = self;
        self.pFloorList.dataSource = self;
        [self.pFloorPanel addSubview:self.pFloorPanelTop];
        [self.pFloorPanel addSubview:self.pFloorList];
        [self.pFloorPanel addSubview:self.pFloorPanelBottom];
        
        float buttonSize = 50.f;
        float labelLength = 200.f;
        float totalPanelLength = buttonSize + labelLength;
        
        self.pDetailsPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_screenWidth * 0.5f - totalPanelLength * 0.5f, m_inactiveDetailPaneYPosition, totalPanelLength, buttonSize)] autorelease];
        
        self.pDismissButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, buttonSize, buttonSize)] autorelease];
        [self.pDismissButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_close_place_pin_off") forState:UIControlStateNormal];
        [self.pDismissButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_close_place_pin_on") forState:UIControlStateHighlighted];
        [self.pDismissButton addTarget:self action:@selector(onCancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.pDetailsPanel addSubview:self.pDismissButton];
        
        self.pFloorNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(buttonSize, 0, labelLength, buttonSize)] autorelease];
        self.pFloorNameLabel.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        self.pFloorNameLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pFloorNameLabel.layer.borderColor = [ExampleApp::Helpers::ColorPalette::MainHudColor CGColor];
        self.pFloorNameLabel.layer.borderWidth = 2.0f;
        self.pFloorNameLabel.textAlignment = NSTextAlignmentCenter;
        [self.pDetailsPanel addSubview:self.pFloorNameLabel];
        
        [self addSubview:self.pDetailsPanel];
        
        m_onScreenParam = 0.f;
        
        [self setHidden:YES];
    }
    
    return self;
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
    self.pFloorPanelBottom.frame = CGRectMake(0, borderHeight+listHeight, floorPanelWidth, borderHeight);
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
    return NO;
}

- (void)setFloorCount:(int)floors :(int)initialFloor
{
    m_floorCount = floors;
    
    [self.pFloorList reloadData];
    [self.pFloorList selectRowAtIndexPath:[NSIndexPath indexPathForRow:(m_floorCount - initialFloor)-1 inSection:0] animated:NO scrollPosition:0];
    [self.pFloorList sizeToFit];
    [self layoutIfNeeded];
    [self setNeedsLayout];
}

- (void) setFloorName:(const std::string*)name;
{
    self.pFloorNameLabel.text = [NSString stringWithUTF8String:name->c_str()];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return m_floorCount;
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
    }
    cell.textLabel.text = [NSString stringWithFormat:@"%d", (m_floorCount - indexPath.item)];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int floorSelected = int((m_floorCount - indexPath.item)-1);
    m_pInterop->SelectFloor(floorSelected);
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
    float newY = m_screenHeight - 50 * onScreenState;
    
    self.hidden = onScreenState == 0.0f;
    self.pFloorPanel.frame.origin = CGPointMake(newX, self.pFloorPanel.frame.origin.y);
    self.pDetailsPanel.frame.origin = CGPointMake(self.pDetailsPanel.frame.origin.x, newY);
    m_onScreenParam = onScreenState;
}

- (void) animateTo:(float)t
{
    float newX = -50 + t * 50;
    float newY = m_screenHeight - 50 * t;
    
    CGRect floorFrame = self.pFloorPanel.frame;
    CGRect detailFrame = self.pDetailsPanel.frame;
    floorFrame.origin.x = newX;
    detailFrame.origin.y = newY;
    
    if(t > 0.f)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.pFloorPanel.frame = floorFrame;
         self.pDetailsPanel.frame = detailFrame;
     }
                     completion:^(BOOL finished)
     {
         self.hidden = (t == 0.0f);
         m_onScreenParam = t;
     }
     ];
}


@end