//
//  UIView+TwitterCardView.m
//  RecceApp
//
//  Created by eeGeo QA on 28/07/2015.
//  Copyright (c) 2015 eeGeo. All rights reserved.
//

#import "TwitterCardView.h"
#import <Accounts/Accounts.h>
#import <Social/Social.h>
#include "App.h"
#include "TwitterDefines.h"
#include "TourExplorerViewInterop.h"
#include <sstream>
#include <string>
#include "ImageStore.h"

@implementation TwitterCardView

- (id) initWithParams:(ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop*)pInterop :(ImageStore*)pImageStore
{
    if (self = [super init])
    {
        m_pInterop = pInterop;
        
        const bool isPhone = App::IsDeviceSmall();
        
        float headerTextSize = isPhone ? 13.0f : 18.0f;
        float screenNameTextSize = isPhone ? 9.0f : 12.0f;
        float textSize = isPhone ? 12.0f : 16.0f;
        
        UIFont* headerFont = [UIFont systemFontOfSize:headerTextSize];
        UIFont* screenNameFont = [UIFont systemFontOfSize:screenNameTextSize];
        UIFont* timeStampFont = screenNameFont;
        UIFont* textFont = [UIFont systemFontOfSize:textSize];
        
        float frameSizeX = isPhone ? 250 : 338;
        float frameSizeY = isPhone ? 164 : 222;
        float bannerHeight = isPhone ? 44.0f : 60.0f;
        float spacing = isPhone ? 3.0f : 4.0f;
        float userImageContainerSize = isPhone ? 59.0f : 80.0f;
        float userImageBorderSize = isPhone ? 3.0f : 4.0f;
        float userImageSize = userImageContainerSize - userImageBorderSize * 2.0f;
        float userImageContainerX = isPhone ? 3.0f : 4.0f;
        float userImageContainerY = isPhone ? 29.0f : 40.0f;
        float nameLabelWidth = frameSizeX - (userImageContainerSize + userImageContainerX + spacing * 4);
        float nameLabelHeight = (float)headerFont.lineHeight + spacing;
        float screenNameLabelHeight = (float)screenNameFont.lineHeight + spacing;
        float nameLabelY = userImageContainerY + userImageContainerSize - screenNameLabelHeight - nameLabelHeight;
        float screenNameLabelY = userImageContainerY + userImageContainerSize - screenNameLabelHeight;
        float timeStampLabelWidth = isPhone ? 38.0f : 50.0f;
        float timeStampLabelHeight = (float)timeStampFont.lineHeight + spacing;
        float timeStampLabelX = frameSizeX - timeStampLabelWidth - 2*spacing;
        float timeStampLabelY = userImageContainerY + userImageContainerSize - screenNameLabelHeight - timeStampLabelHeight;
        float tweetContentY = userImageContainerY + userImageContainerSize + spacing * 2.0f;
        float tweetContentHeight = frameSizeY - tweetContentY - 2*spacing;
        float tweetContentWidth = frameSizeX - 6*spacing;
        float tappableTopSectionHeight = userImageContainerY + userImageContainerSize;
        
        self.frame = CGRectMake(0, 0, frameSizeX, frameSizeY);
        self.backgroundColor = [UIColor whiteColor];
        
        self.pTappableTopSection = [[UIView alloc] initWithFrame:CGRectMake(0, 0, frameSizeX, tappableTopSectionHeight)];
        self.pTappableTopSection.backgroundColor = [UIColor clearColor];
        self.pTappableTopSection.userInteractionEnabled = YES;
        [self addSubview:self.pTappableTopSection];
        
        self.pBannerImage = [[[FXImageView alloc] initWithFrame:CGRectMake(0, 0, frameSizeX, bannerHeight)]autorelease];
        self.pBannerImage.contentMode = UIViewContentModeScaleAspectFill;
        self.pBannerImage.asynchronous = YES;
        [self addSubview:self.pBannerImage];
        
        self.pUserImageContainer = [[UIView alloc] initWithFrame:CGRectMake(userImageContainerX, userImageContainerY, userImageContainerSize, userImageContainerSize)];
        self.pUserImageContainer.backgroundColor = [UIColor whiteColor];
        self.pUserImageContainer.userInteractionEnabled = NO;
        [self addSubview:self.pUserImageContainer];
        
        self.pUserImage = [[[FXImageView alloc] initWithFrame:CGRectMake(userImageBorderSize, userImageBorderSize, userImageSize, userImageSize)]autorelease];
        self.pUserImage.contentMode = UIViewContentModeScaleAspectFill;
        self.pUserImage.asynchronous = YES;
        [self.pUserImageContainer addSubview:self.pUserImage];
        
        self.pNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(userImageContainerSize + userImageContainerX + spacing, nameLabelY, nameLabelWidth, nameLabelHeight)];
        self.pNameLabel.textColor = TwitterDefines::DarkTextColor;
        self.pNameLabel.font = headerFont;
        [self addSubview:self.pNameLabel];
        
        
        self.pScreenNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(userImageContainerSize + userImageContainerX + spacing, screenNameLabelY, nameLabelWidth, screenNameLabelHeight)];
        self.pScreenNameLabel.textColor = TwitterDefines::LightTextColor;
        self.pScreenNameLabel.font = screenNameFont;
        [self addSubview:self.pScreenNameLabel];
        
        self.pTimeStampLabel = [[UILabel alloc] initWithFrame:CGRectMake(timeStampLabelX, timeStampLabelY, timeStampLabelWidth, timeStampLabelHeight)];
        self.pTimeStampLabel.textColor = TwitterDefines::LightTextColor;
        self.pTimeStampLabel.font = timeStampFont;
        self.pTimeStampLabel.textAlignment = NSTextAlignmentRight;
        [self addSubview:self.pTimeStampLabel];
        
        self.pTweetContent = [[UITextView alloc] initWithFrame:CGRectMake(2*spacing, tweetContentY, tweetContentWidth, tweetContentHeight)];
        self.pTweetContent.font = textFont;
        self.pTweetContent.scrollEnabled = NO;
        self.pTweetContent.editable = NO;
        self.pTweetContent.textColor = TwitterDefines::DarkTextColor;
        self.pTweetContent.linkTextAttributes = @{NSForegroundColorAttributeName:TwitterDefines::LinkColor};
        self.pTweetContent.textContainer.lineFragmentPadding = 0;
        self.pTweetContent.textContainerInset = UIEdgeInsetsZero;
        self.pTweetContent.delegate = self;
        [self addSubview:self.pTweetContent];
        
        m_pTopSectionTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleProfileTapped:)];
        [m_pTopSectionTapGestureRecognizer setDelegate:self];
        [self.pTappableTopSection addGestureRecognizer:m_pTopSectionTapGestureRecognizer];
        
        m_pImageStore = pImageStore;
    }
    return self;
}

- (void) dealloc
{
    [self clearImages];
    
    [self.pTappableTopSection removeGestureRecognizer:m_pTopSectionTapGestureRecognizer];
    [m_pTopSectionTapGestureRecognizer release];
    m_pTopSectionTapGestureRecognizer = nil;
    
    [self.pTweetContent removeFromSuperview];
    [self.pTweetContent release];
    self.pTweetContent = nil;
    
    [self.pTimeStampLabel removeFromSuperview];
    [self.pTimeStampLabel release];
    self.pTimeStampLabel = nil;
    
    [self.pScreenNameLabel removeFromSuperview];
    [self.pScreenNameLabel release];
    self.pScreenNameLabel = nil;
    
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];
    self.pNameLabel = nil;
    
    [self.pUserImage removeFromSuperview];
    [self.pUserImage release];
    self.pUserImage = nil;
    
    [self.pUserImageContainer removeFromSuperview];
    [self.pUserImageContainer release];
    self.pUserImageContainer = nil;
    
    [self.pBannerImage removeFromSuperview];
    [self.pBannerImage release];
    self.pBannerImage = nil;
    
    [self.m_pTwitterId release];
    self.m_pTwitterId = nil;
    
    [self.m_pUserName release];
    self.m_pUserName = nil;
    
    [self.m_pScreenName release];
    self.m_pScreenName = nil;
    
    [self.pTappableTopSection removeFromSuperview];
    [self.pTappableTopSection release];
    self.pTappableTopSection = nil;
    
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

- (void)setContent:(NSString*)strName
        screenName:(NSString*)strScreenName
      tweetContent:(NSString*)strTweetContent
         userImage:(NSString*)strUserImagePath
       bannerImage:(NSString*)strBannerImagePath
         createdAt:(NSString*)strCreatedAt
      profileColor:(NSString*)strProfileColor
           tweetId:(NSString*)strId
       tweetCutoff:(NSInteger)intTweetCutoff
       doesLinkOut:(BOOL)bDoesLinkOut
      deeplinkUrls:(NSMutableArray*)arrDeeplinkUrls
          linkUrls:(NSMutableArray*)arrLinkUrls
  linkStartIndices:(NSMutableArray*)arrLinkStartIndices
    linkEndIndices:(NSMutableArray*)arrLinkEndIndices
{
    self.m_pTwitterId = strId;
    self.m_pUserName = strName;
    self.m_pScreenName = strScreenName;
    
    [self.pNameLabel setText:strName];
    
    NSString *screenNameText = [NSString stringWithFormat:@"@%@", strScreenName];
    [self.pScreenNameLabel setText:screenNameText];
    
    // MB: Issue in ios 7.0 with UITextViews in recreated views not clearing their link attributes.  Workaround is to set text to nil before replacing.
    // http://stackoverflow.com/questions/19121367/uitextviews-in-a-uitableview-link-detection-bug-in-ios-7
    [self.pTweetContent setText:nil];
    [self.pTweetContent setText:strTweetContent];
    
    if(intTweetCutoff < strTweetContent.length - 1)
    {
        strTweetContent = [strTweetContent substringToIndex:intTweetCutoff];
    }
    
    NSMutableAttributedString* tweetContent = [[NSMutableAttributedString alloc] initWithString:strTweetContent];
    
    float textSize = self.pTweetContent.font.pointSize;
    
    [tweetContent addAttribute:NSFontAttributeName value:[UIFont systemFontOfSize:textSize] range:NSMakeRange(0, strTweetContent.length)];
    
    for (int i = 0; i < arrLinkUrls.count; ++i)
    {
        NSInteger startIndex = [arrLinkStartIndices[i] integerValue];
        NSInteger endIndex = [arrLinkEndIndices[i] integerValue];
        
        if(endIndex >= tweetContent.length)
        {
            if (startIndex >= tweetContent.length - 1)
            {
                // tweet has been truncated (due to addition of retweet info at start), link is not on screen
                continue;
            }
            
            // this link continues past the character limit, clamp to end of text
            endIndex = tweetContent.length - 1;
        }
        
        if(m_pInterop->CanHandleDeeplinkURL( [arrDeeplinkUrls[i] UTF8String] ))
        {
            [tweetContent addAttribute:NSLinkAttributeName value:arrDeeplinkUrls[i]
                                 range:NSMakeRange(startIndex, endIndex - startIndex + 1)];
        }
        else
        {
            [tweetContent addAttribute:NSLinkAttributeName value:arrLinkUrls[i]
                                 range:NSMakeRange(startIndex, endIndex - startIndex + 1)];
        }
    }
    
    [self.pTweetContent setAttributedText:tweetContent];
    
    [m_pImageStore loadImage:[strUserImagePath UTF8String]
                            :self.pUserImage
                            :^(UIImage* image)
                             {
                                 [self.pUserImage setImage:image];
                             }];
    
    [self.pBannerImage setImage:nil];
    if([strBannerImagePath length] > 0)
    {
        [m_pImageStore loadImage:[strBannerImagePath UTF8String]
                                :self.pBannerImage
                                :^(UIImage* image)
                                 {
                                     [self.pBannerImage setImage:image];
                                 }];
    }
    else
    {
        unsigned profileColorInt = 0;
        NSScanner *scanner = [NSScanner scannerWithString:strProfileColor];
        
        [scanner scanHexInt:&profileColorInt];
        
        UIColor* profileColor = [UIColor colorWithRed:(float)((profileColorInt & 0xFF0000) >> 16) / 255.0f
                                                green:(float)((profileColorInt & 0x00FF00) >> 8) / 255.0f
                                                 blue:(float)((profileColorInt & 0x0000FF)) / 255.0f
                                                alpha:1.0f];
        
        self.pBannerImage.backgroundColor = profileColor;
    }
    
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setDateFormat:@"EE LLL d HH:mm:ss Z yyyy"];
    NSDate *date = [dateFormat dateFromString:strCreatedAt];
    
    int secondsSinceCreated = (int)[[NSDate date] timeIntervalSinceDate:date];
    
    NSString* timeString = @"";
    
    if(secondsSinceCreated < 60)
    {
        timeString = [NSString stringWithFormat:@"%ds", secondsSinceCreated];
    }
    else if (secondsSinceCreated < 3600)
    {
        timeString = [NSString stringWithFormat:@"%dm", secondsSinceCreated / 60];
    }
    else if (secondsSinceCreated < 86400)
    {
        timeString = [NSString stringWithFormat:@"%dh", secondsSinceCreated / 3600];
    }
    else
    {
        [dateFormat setDateFormat:@"dd"];
        NSString* dayString = [dateFormat stringFromDate:date];
        
        [dateFormat setDateFormat:@"MMM"];
        NSString* monthString = [dateFormat stringFromDate:date];
        
        timeString = [timeString stringByAppendingString:dayString];
        timeString = [timeString stringByAppendingString:@" "];
        timeString = [timeString stringByAppendingString:monthString];
    }
    
    [dateFormat release];
    
    [self.pTimeStampLabel setText:timeString];
    
    if(bDoesLinkOut)
    {
        [m_pTopSectionTapGestureRecognizer removeTarget:nil action:NULL];
        [m_pTopSectionTapGestureRecognizer addTarget:self action:@selector(handleTourChangeRequest:)];
    }
    else
    {
        [m_pTopSectionTapGestureRecognizer removeTarget:nil action:NULL];
        [m_pTopSectionTapGestureRecognizer addTarget:self action:@selector(handleProfileTapped:)];
    }
}

- (void) clearImages
{
    [m_pImageStore releaseImageForView:self.pBannerImage];
    [m_pImageStore releaseImageForView:self.pUserImage];
}

- (void) loadImage: (NSString*)imagePath :(FXImageView*)imageView
{
    if([imagePath rangeOfString:@"http"].location == 0)
    {
        NSURL* url = [NSURL URLWithString:imagePath];
        [imageView setImageWithContentsOfURL:url];
    }
    else
    {
        [imageView setImageWithContentsOfFile:imagePath];
    }
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) handleProfileTapped:(UITapGestureRecognizer *)tap
{
    std::string httpFallbackUrl =  std::string("https://twitter.com/") + [self.m_pScreenName UTF8String];
    
    std::string twitterDeeplinkUrl = std::string("twitter://user?screen_name=") + [self.m_pScreenName UTF8String];
    
    m_pInterop->ShowDeeplinkURL(twitterDeeplinkUrl, httpFallbackUrl);
}

- (void)handleTourChangeRequest:(UITapGestureRecognizer *)tap
{
    m_pInterop->OnChangeTourRequested([self.m_pUserName UTF8String]);
}


- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)url inRange:(NSRange)characterRange
{
    // Deeplinking check and setup in setContent
    m_pInterop->ShowExternalURL([[url absoluteString] UTF8String]);
    
    return NO;
}

@end
