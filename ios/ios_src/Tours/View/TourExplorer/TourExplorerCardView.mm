// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "TourExplorerCardView.h"
#include "App.h"
#include "ImageHelpers.h"
#include "TourDefines.h"

@implementation TourExplorerCardView
{
    float m_textContainerY;
    float m_textContainerYNoDescription;
}

- (id) init
{
    if (self = [super init])
    {
        const bool isPhone = App::IsDeviceSmall();
        
        float frameSizeX = isPhone ? 250 : 338;
        float frameSizeY = isPhone ? 164 : 222;
        
        float textSpacingX = isPhone ? 4.0f : 7.0f;
        float textSpacingY = isPhone ? 3.0f : 5.0f;
        
        float textSize = isPhone ? 14.0f : 17.0f;
        float detailTextSize = isPhone ? 11.0f : 14.0f;
        
        UIFont* textFont = [UIFont systemFontOfSize:textSize];
        UIFont* detailTextFont = [UIFont systemFontOfSize:detailTextSize];
        
        float textHeight = textFont.lineHeight + 1.0f;
        float detailTextHeight = 2.0f*(detailTextFont.lineHeight + 1.0f);
        float detailTextBackgroundHeight = detailTextHeight + textSpacingY * 2.0f;
        
        m_textContainerY = frameSizeY - (detailTextBackgroundHeight + textHeight + textSpacingY * 2.0f);
        m_textContainerYNoDescription = m_textContainerY + detailTextBackgroundHeight;
        
        self.frame = CGRectMake(0, 0, frameSizeX, frameSizeY);
        self.backgroundColor = [UIColor whiteColor];
        
        self.pBackgroundImage = [[FXImageView alloc]initWithFrame:CGRectMake(0.0f, 0.0f, frameSizeX, frameSizeY)];
        self.pBackgroundImage.contentMode = UIViewContentModeScaleAspectFill;
        self.pBackgroundImage.asynchronous = YES;
        [self addSubview:self.pBackgroundImage];
        
        self.pTextContainer = [[UIView alloc]initWithFrame:CGRectMake(0.0f, m_textContainerY, frameSizeX, textHeight + textSpacingY * 2.0f)];
        self.pTextContainer.backgroundColor = [UIColor clearColor];
        [self.pBackgroundImage addSubview:self.pTextContainer];
        
        CAGradientLayer *gradient = [CAGradientLayer layer];
        gradient.frame =  CGRectMake(0.f, 0.f, self.pTextContainer.bounds.size.width, self.pTextContainer.bounds.size.height);
        
        UIColor *topColor = [UIColor clearColor];
        UIColor *bottomColor = [UIColor blackColor];
        gradient.colors = [NSArray arrayWithObjects:(id)[topColor CGColor], (id)[bottomColor CGColor], nil];
        
        [self.pTextContainer.layer insertSublayer:gradient atIndex:0];
        
        self.pTextLabel = [[UILabel alloc]initWithFrame:CGRectMake(textSpacingX, textSpacingY, frameSizeX - textSpacingX * 2.0f, textHeight)];
        self.pTextLabel.textColor = [UIColor whiteColor];
        self.pTextLabel.font = textFont;
        [self.pTextContainer addSubview:self.pTextLabel];
        
        self.pDetailTextContainer = [[UIView alloc]initWithFrame:CGRectMake(0.0f, frameSizeY - detailTextBackgroundHeight, frameSizeX, detailTextBackgroundHeight)];
        self.pDetailTextContainer.backgroundColor = [UIColor whiteColor];
        [self.pBackgroundImage addSubview:self.pDetailTextContainer];
        
        self.pDetailTextLabel = [[UILabel alloc]initWithFrame:CGRectMake(textSpacingX, textSpacingY, frameSizeX - textSpacingX * 2.0f, detailTextHeight)];
        self.pDetailTextLabel.numberOfLines = 0;
        self.pDetailTextLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pDetailTextLabel.textColor = TourDefines::LightTextColor;
        self.pDetailTextLabel.font = detailTextFont;
        [self.pDetailTextContainer addSubview:self.pDetailTextLabel];
    }
    return self;
}

- (void) dealloc
{
    [self.pDetailTextLabel removeFromSuperview];
    [self.pDetailTextLabel release];
    self.pDetailTextLabel = nil;
    
    [self.pDetailTextContainer removeFromSuperview];
    [self.pDetailTextContainer release];
    self.pDetailTextContainer = nil;
    
    [self.pTextLabel removeFromSuperview];
    [self.pTextLabel release];
    self.pTextLabel = nil;
    
    [self.pTextContainer removeFromSuperview];
    [self.pTextContainer release];
    self.pTextContainer = nil;
    
    [self.pBackgroundImage removeFromSuperview];
    [self.pBackgroundImage release];
    self.pBackgroundImage = nil;
    
    [super dealloc];
}

- (void)layoutSubviews
{
    self.layer.shadowRadius = 5.0f;
    self.layer.shadowColor = [UIColor blackColor].CGColor;
    self.layer.shadowOffset = CGSizeMake(0.0f, 2.0f);
    self.layer.shadowOpacity = 0.5f;
    self.layer.shadowPath = [UIBezierPath bezierPathWithRect:self.bounds].CGPath;
    self.layer.masksToBounds = NO;
    
    [super layoutSubviews];
}

- (void)setContent:(NSString*)strImagePath
                  :(NSString*)strText
                  :(NSString*)strDetailText
{
    self.pBackgroundImage.image = [UIImage imageNamed:strImagePath];
    if(self.pBackgroundImage.image == nil)
    {
        self.pBackgroundImage.image = ExampleApp::Helpers::ImageHelpers::ImageFromColor([UIColor darkGrayColor]);
    }
    
    self.pTextLabel.text = strText;
    
    float textContainerY = 0.0f;
    
    if(strDetailText.length == 0)
    {
        [self.pDetailTextContainer setHidden:YES];
        
        textContainerY = m_textContainerYNoDescription;
    }
    else
    {
        [self.pDetailTextContainer setHidden:NO];
        
        self.pDetailTextLabel.text = strDetailText;
        
        textContainerY = m_textContainerY;
    }
    
    CGRect textLabelFrame = self.pTextContainer.frame;
    textLabelFrame.origin.y = textContainerY;
    self.pTextContainer.frame = textLabelFrame;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

@end
