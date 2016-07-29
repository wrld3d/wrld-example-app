// Copyright eeGeo Ltd (2016), All Rights Reserved

#include "InteriorsExplorerTutorialView.h"
#include "UIColors.h"
#include "UIHelpers.h"
#include "ImageHelpers.h"
#include "InteriorsExplorerFloorItemView.h"

namespace
{
    const int dialogOutlineSize = 2;
}

@implementation InteriorsExplorerTutorialView

- (id) initWithParams: (float) width : (float) height : (float) pixelScale
{
    if (self = [super init])
    {
        m_animationTimeSeconds = 0.25f;
        
        m_showChangeFloorDialog = true;
        
        const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
        
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_pixelScale = pixelScale;
        
        m_arrowLength = isPhone ? 20 : 30;
        m_arrowWidth = isPhone ? 10 : 15;
        
        m_iconPaddingTop = isPhone ? 9 : 13;
        m_iconPaddingLeft = isPhone ? 8 : 18;
        m_iconSize = isPhone ? 18 : 28;
        
        self.frame = CGRectMake(0,
                                0,
                                m_screenWidth,
                                m_screenHeight);
        
        const int dialogWidth = isPhone ? 185 : 260;
        const int dialogHeight = isPhone ? 87 : 122;
        
        
        self.pExitDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0,
                                                                              0,
                                                                              dialogWidth + (dialogOutlineSize * 2),
                                                                              dialogHeight + (dialogOutlineSize * 2))] autorelease];
        self.pExitDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pExitDialogContainer];
        
        self.pExitDialogOutlineArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pExitDialogContainer,
                                                                                                  "arrow3_right_blue",
                                                                                                  dialogWidth + dialogOutlineSize,
                                                                                                  (dialogHeight + (dialogOutlineSize * 2)) / 2 - (m_arrowWidth + (dialogOutlineSize * 2)) / 2,
                                                                                                  m_arrowLength + (dialogOutlineSize * 2),
                                                                                                  m_arrowWidth + (dialogOutlineSize * 2));
        
        self.pExitDialogLabel = [[[UIView alloc] initWithFrame:CGRectMake(dialogOutlineSize,
                                                                          dialogOutlineSize,
                                                                          dialogWidth,
                                                                          dialogHeight)] autorelease];
        self.pExitDialogLabel.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pExitDialogContainer addSubview: self.pExitDialogLabel];
        
        self.pExitDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pExitDialogLabel, "arrow3_right", dialogWidth, dialogHeight/2 - m_arrowWidth/2, m_arrowLength, m_arrowWidth);
        
        self.pExitDialogIcon = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pExitDialogLabel, "Alert_Tutorial_icon", m_iconPaddingLeft, m_iconPaddingTop, m_iconSize, m_iconSize);
        
        self.pExitDialogTitle = [self createDialogTitle:@"Exit Indoors"];
        [self.pExitDialogLabel addSubview:self.pExitDialogTitle];
        
        self.pExitDialogDescription = [self createDialogDescription:@"Press the exit button to\ngo back outside."];
        [self.pExitDialogLabel addSubview:self.pExitDialogDescription];
        self.pExitDialogContainer.alpha = 0.0f;
        [self.pExitDialogContainer setHidden:true];
        
        
        self.pChangeFloorDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0,
                                                                                     0,
                                                                                     dialogWidth + (dialogOutlineSize * 2),
                                                                                     dialogHeight + (dialogOutlineSize * 2))] autorelease];
        self.pChangeFloorDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pChangeFloorDialogContainer];
        
        self.pChangeFloorDialogOutlineArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pChangeFloorDialogContainer,
                                                                                                         "arrow3_right_blue",
                                                                                                         dialogWidth + dialogOutlineSize,
                                                                                                         (dialogHeight + (dialogOutlineSize * 2)) / 2 - (m_arrowWidth + (dialogOutlineSize * 2)) / 2,
                                                                                                         m_arrowLength + (dialogOutlineSize * 2),
                                                                                                         m_arrowWidth + (dialogOutlineSize * 2));
        
        self.pChangeFloorDialogLabel = [[[UIView alloc] initWithFrame:CGRectMake(dialogOutlineSize,
                                                                                 dialogOutlineSize,
                                                                                 dialogWidth,
                                                                                 dialogHeight)] autorelease];
        self.pChangeFloorDialogLabel.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pChangeFloorDialogContainer addSubview: self.pChangeFloorDialogLabel];
        
        self.pChangeFloorDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pChangeFloorDialogLabel, "arrow3_right", dialogWidth, dialogHeight/2 - m_arrowWidth/2, m_arrowLength, m_arrowWidth);
        
        self.pChangeFloorDialogIcon = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pChangeFloorDialogLabel, "Alert_Tutorial_icon", m_iconPaddingLeft, m_iconPaddingTop, m_iconSize, m_iconSize);
        
        self.pChangeFloorDialogTitle = [self createDialogTitle:@"Change Floors"];
        [self.pChangeFloorDialogLabel addSubview:self.pChangeFloorDialogTitle];
        
        self.pChangeFloorDialogDescription = [self createDialogDescription:@"Slide the elevator button\nup and down to move\nbetween floors."];
        [self.pChangeFloorDialogLabel addSubview:self.pChangeFloorDialogDescription];
        self.pChangeFloorDialogContainer.alpha = 0.0f;
        [self.pChangeFloorDialogContainer setHidden:true];
        
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)];
        [m_tapGestureRecogniser setDelegate:self];
        self.userInteractionEnabled = YES;
        [self addGestureRecognizer:m_tapGestureRecogniser];
    }
    
    return self;
}

- (UILabel*) createDialogTitle: (NSString*) text
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    pLabel.text = text;
    pLabel.font = useSmallScreen ? [UIFont systemFontOfSize:14.5f] : [UIFont systemFontOfSize:18.0f];
    return pLabel;
}

- (UITextView*) createDialogDescription: (NSString*) text
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    UITextView* pTextView = [[[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pTextView.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    pTextView.editable = NO;
    pTextView.scrollEnabled = NO;
    pTextView.font = useSmallScreen ? [UIFont systemFontOfSize:13.0f] : [UIFont systemFontOfSize:16.0f];
    pTextView.textContainer.lineFragmentPadding = 0;
    pTextView.textContainerInset = UIEdgeInsetsZero;
    pTextView.text = text;
    return pTextView;
}

- (void) layoutSubviews
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    m_screenWidth = self.superview.bounds.size.width;
    m_screenHeight = self.superview.bounds.size.height;
    [self setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
    
    CGRect dialogFrame = self.pExitDialogContainer.frame;
    int dialogWidth = dialogFrame.size.width;
    int dialogHeight = dialogFrame.size.height;
    int textPaddingLeft = (m_iconPaddingLeft * 2) + m_iconSize;
    int textPaddingRight = 4;
    int titlePaddingTop = isPhone ? 9 : 17;
    int descriptionPaddingTop = isPhone ? 4 : 9;
    
    CGSize exitTitleTextSize = [self.pExitDialogTitle sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
    float exitTitleWidth = dialogWidth-(textPaddingLeft + textPaddingRight);
    
    CGRect exitTitleRect = CGRectMake(textPaddingLeft, titlePaddingTop, exitTitleWidth, exitTitleTextSize.height);
    [self.pExitDialogTitle setFrame:exitTitleRect];
    
    float exitDescriptionHeight = dialogHeight - exitTitleTextSize.height - (titlePaddingTop * 2);
    float exitDescriptonWidth = exitTitleWidth;
    
    CGRect exitDescriptonRect = CGRectMake(textPaddingLeft, exitTitleTextSize.height + titlePaddingTop + descriptionPaddingTop, exitDescriptonWidth, exitDescriptionHeight);
    [self.pExitDialogDescription setFrame:exitDescriptonRect];
    
    
    CGSize changeFloorTitleTextSize = [self.pChangeFloorDialogTitle sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
    float changeFloorTitleWidth = dialogWidth-(textPaddingLeft + textPaddingRight);
    
    CGRect changeFloorTitleRect = CGRectMake(textPaddingLeft, titlePaddingTop, changeFloorTitleWidth, changeFloorTitleTextSize.height);
    [self.pChangeFloorDialogTitle setFrame:changeFloorTitleRect];
    
    float changeFloorsDescriptionHeight = dialogHeight - changeFloorTitleTextSize.height - (titlePaddingTop * 2);
    float changeFloorsDescriptonWidth = changeFloorTitleWidth;
    
    CGRect changeFloorsDescriptonRect = CGRectMake(textPaddingLeft, changeFloorTitleTextSize.height + titlePaddingTop + descriptionPaddingTop, changeFloorsDescriptonWidth, changeFloorsDescriptionHeight);
    [self.pChangeFloorDialogDescription setFrame:changeFloorsDescriptonRect];
}

- (BOOL) consumesTouch
{
    if(!self.pExitDialogContainer.hidden)
    {
        return YES;
    }

    return NO;
}

- (void) _tapTabGesture: (UITapGestureRecognizer*) recognizer
{
    [self dismiss];
}

- (void) repositionTutorialDialogs: (float) newPositionX
                                  : (float) dismissButtonPositionY
                                  : (float) dismissButtonHeight
                                  : (float) floorChangeButtonPositionY
                                  : (float) floorChangeButtonHeight
                                  : (bool) showChangeFloorDialog
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    CGRect dialogFrame = self.pExitDialogContainer.frame;
    int dialogWidth = dialogFrame.size.width;
    int dialogHeight = dialogFrame.size.height;
    int arrowLength = isPhone ? 20 : 30;
    int dialogMargin = (isPhone ? 79 : 95);
    
    CGRect exitDialogFrame = self.pExitDialogContainer.frame;
    exitDialogFrame.origin.x = newPositionX - (dialogWidth + (dialogOutlineSize * 2) + arrowLength + dialogMargin);
    exitDialogFrame.origin.y = (dismissButtonPositionY + dismissButtonHeight / 2) - ((dialogHeight + (dialogOutlineSize * 2)) / 2);
    self.pExitDialogContainer.frame = exitDialogFrame;
    
    CGRect changeFloorDialogFrame = self.pChangeFloorDialogContainer.frame;
    changeFloorDialogFrame.origin.x = newPositionX - (dialogWidth + (dialogOutlineSize * 2) + arrowLength + dialogMargin);
    changeFloorDialogFrame.origin.y = (floorChangeButtonPositionY + floorChangeButtonHeight / 2) - ((dialogHeight + (dialogOutlineSize * 2)) / 2);
    self.pChangeFloorDialogContainer.frame = changeFloorDialogFrame;
    
    m_showChangeFloorDialog = showChangeFloorDialog;
}

- (void) animateTo: (float) t
{
    self.pExitDialogContainer.alpha = 0.0f;
    [self.pExitDialogContainer setHidden:NO];
    
    self.pChangeFloorDialogContainer.alpha = 0.0f;
    if(m_showChangeFloorDialog)
    {
        [self.pChangeFloorDialogContainer setHidden:NO];
    }
    else
    {
        [self.pChangeFloorDialogContainer setHidden:YES];
    }
    
    [UIView animateWithDuration:m_animationTimeSeconds
                          delay:0.0f
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^
    {
        self.pExitDialogContainer.alpha = t;
    }
                     completion:^(BOOL finished)
    {
        if(self.pExitDialogContainer.alpha <= 0.0f)
        {
            [self.pExitDialogContainer setHidden:YES];
        }
    }];
    
    [UIView animateWithDuration:m_animationTimeSeconds
                          delay:m_animationTimeSeconds * 0.8f
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^
     {
         self.pChangeFloorDialogContainer.alpha = t;
     }
                     completion:^(BOOL finished)
     {
         if(self.pChangeFloorDialogContainer.alpha <= 0.0f)
         {
             [self.pChangeFloorDialogContainer setHidden:YES];
             [self hide];
         }
     }];
}

-(void) dismiss
{
    [self animateTo:0.0f];
}

- (void)dealloc
{
    [m_tapGestureRecogniser release];
    
    [self.pExitDialogIcon removeFromSuperview];
    [self.pExitDialogIcon release];
    [self.pExitDialogArrow removeFromSuperview];
    [self.pExitDialogArrow release];
    [self.pExitDialogTitle removeFromSuperview];
    [self.pExitDialogTitle release];
    [self.pExitDialogDescription removeFromSuperview];
    [self.pExitDialogDescription release];
    [self.pExitDialogLabel removeFromSuperview];
    [self.pExitDialogLabel release];
    [self.pExitDialogOutlineArrow removeFromSuperview];
    [self.pExitDialogOutlineArrow release];
    [self.pExitDialogContainer removeFromSuperview];
    [self.pExitDialogContainer release];
    
    [self.pChangeFloorDialogIcon removeFromSuperview];
    [self.pChangeFloorDialogIcon release];
    [self.pChangeFloorDialogArrow removeFromSuperview];
    [self.pChangeFloorDialogArrow release];
    [self.pChangeFloorDialogTitle removeFromSuperview];
    [self.pChangeFloorDialogTitle release];
    [self.pChangeFloorDialogDescription removeFromSuperview];
    [self.pChangeFloorDialogDescription release];
    [self.pChangeFloorDialogLabel removeFromSuperview];
    [self.pChangeFloorDialogLabel release];
    [self.pChangeFloorDialogOutlineArrow removeFromSuperview];
    [self.pChangeFloorDialogOutlineArrow release];
    [self.pChangeFloorDialogContainer removeFromSuperview];
    [self.pChangeFloorDialogContainer release];
    
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

@end