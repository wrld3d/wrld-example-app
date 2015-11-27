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
        
        float frameSizeX = isPhone ? 250 : 338;
        float frameSizeY = isPhone ? 164 : 222;
        float bannerHeight = isPhone ? 36.0f : 60.0f;
        float spacing = isPhone ? 3.0f : 4.0f;
        float userImageContainerSize = isPhone ? 48.0f : 80.0f;
        float userImageBorderSize = isPhone ? 3.0f : 4.0f;
        float userImageSize = userImageContainerSize - userImageBorderSize * 2.0f;
        float userImageContainerX = isPhone ? 3.0f : 4.0f;
        float userImageContainerY = isPhone ? 24.0f : 40.0f;
        float nameLabelWidth = frameSizeX - (userImageSize + userImageContainerX + spacing * 4);
        float nameLabelHeight = isPhone ? 15 : 21;
        float screenNameLabelHeight = isPhone ? 13 : 17;
        float timeStampLabelWidth = isPhone ? 40.0f : 50.0f;
        float timeStampLabelX = frameSizeX - timeStampLabelWidth - spacing;
        float tweetContentHeight = isPhone ? 70 : 90;
        float tweetContentY = bannerHeight + nameLabelHeight + screenNameLabelHeight + spacing * 2.0f;
        float bottomButtonsSize = 16;
        float bottomButtonsY = frameSizeY - (bottomButtonsSize + spacing * 2.0f);
        float twitterBrandIconSize = isPhone ? 30.0f : 40.0f;
        
        self.frame = CGRectMake(0, 0, frameSizeX, frameSizeY);
        self.backgroundColor = [UIColor whiteColor];
        
        self.pBannerImage = [[[FXImageView alloc] initWithFrame:CGRectMake(0, 0, frameSizeX, bannerHeight)]autorelease];
        self.pBannerImage.contentMode = UIViewContentModeScaleAspectFill;
        self.pBannerImage.asynchronous = YES;
        self.pBannerImage.userInteractionEnabled = YES;
        [self addSubview:self.pBannerImage];
        
        self.pUserImageContainer = [[UIView alloc] initWithFrame:CGRectMake(userImageContainerX, userImageContainerY, userImageContainerSize, userImageContainerSize)];
        self.pUserImageContainer.backgroundColor = [UIColor whiteColor];
        [self addSubview:self.pUserImageContainer];
        
        self.pUserImage = [[[FXImageView alloc] initWithFrame:CGRectMake(userImageBorderSize, userImageBorderSize, userImageSize, userImageSize)]autorelease];
        self.pUserImage.contentMode = UIViewContentModeScaleAspectFill;
        self.pUserImage.asynchronous = YES;
        self.pUserImage.userInteractionEnabled = YES;
        [self.pUserImageContainer addSubview:self.pUserImage];
        
        self.pTwitterBrandIcon = [[[FXImageView alloc] initWithFrame:CGRectMake(userImageContainerX + userImageContainerSize * 0.5f - twitterBrandIconSize * 0.5f,
                                                                                userImageContainerY + userImageContainerSize + userImageContainerSize * 0.5f - twitterBrandIconSize * 0.5f,
                                                                                twitterBrandIconSize,
                                                                                twitterBrandIconSize)] autorelease];
        self.pTwitterBrandIcon.contentMode = UIViewContentModeScaleAspectFill;
        self.pTwitterBrandIcon.image = [UIImage imageNamed:@"Tours/States/Twitter/tweet_bird"];
        [self addSubview: self.pTwitterBrandIcon];
                                                                                
        float headerTextSize = isPhone ? 14.0f : 17.0f;
        float screenNameTextSize = isPhone ? 9.0f : 12.0f;
        float textSize = isPhone ? 11.0f : 14.0f;
        
        self.pNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(userImageContainerSize + userImageContainerX + spacing, bannerHeight + spacing, nameLabelWidth, nameLabelHeight)];
        self.pNameLabel.textColor = TwitterDefines::DarkTextColor;
        self.pNameLabel.font = [UIFont systemFontOfSize:headerTextSize];
        self.pNameLabel.userInteractionEnabled = YES;
        [self addSubview:self.pNameLabel];
        
        
        self.pScreenNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(userImageContainerSize + userImageContainerX + spacing, bannerHeight + spacing + nameLabelHeight, nameLabelWidth, screenNameLabelHeight)];
        self.pScreenNameLabel.textColor = TwitterDefines::LightTextColor;
        self.pScreenNameLabel.font = [UIFont systemFontOfSize:screenNameTextSize];
        self.pScreenNameLabel.userInteractionEnabled = YES;
        [self addSubview:self.pScreenNameLabel];
        
        self.pTimeStampLabel = [[UILabel alloc] initWithFrame:CGRectMake(timeStampLabelX, bannerHeight + spacing, timeStampLabelWidth, screenNameLabelHeight)];
        self.pTimeStampLabel.textColor = TwitterDefines::LightTextColor;
        self.pTimeStampLabel.font = [UIFont systemFontOfSize:textSize];
        self.pTimeStampLabel.textAlignment = NSTextAlignmentRight;
        [self addSubview:self.pTimeStampLabel];
        
        self.pTweetContent = [[UITextView alloc] initWithFrame:CGRectMake(userImageContainerSize + userImageContainerX + spacing, tweetContentY, nameLabelWidth, tweetContentHeight)];
        self.pTweetContent.font = [UIFont systemFontOfSize:textSize];
        self.pTweetContent.scrollEnabled = NO;
        self.pTweetContent.editable = NO;
        self.pTweetContent.textColor = TwitterDefines::DarkTextColor;
        self.pTweetContent.linkTextAttributes = @{NSForegroundColorAttributeName:TwitterDefines::LinkColor};
        self.pTweetContent.textContainer.lineFragmentPadding = 0;
        self.pTweetContent.textContainerInset = UIEdgeInsetsZero;
        self.pTweetContent.delegate = self;
        [self addSubview:self.pTweetContent];
        
        
        self.pMoreDetailsLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, bottomButtonsY, frameSizeX, screenNameLabelHeight)];
        [self.pMoreDetailsLabel setUserInteractionEnabled:NO];
        self.pMoreDetailsLabel.textAlignment = NSTextAlignmentCenter;
        self.pMoreDetailsLabel.textColor = [UIColor lightGrayColor];
        self.pMoreDetailsLabel.font = [UIFont systemFontOfSize:textSize];
        NSMutableAttributedString* attrString = [[NSMutableAttributedString alloc] initWithString:@"Tweet Details"];
        [attrString addAttribute:NSUnderlineStyleAttributeName value:[NSNumber numberWithInt:1] range:(NSRange){0, attrString.length}];
        self.pMoreDetailsLabel.attributedText = attrString;
        [self addSubview:self.pMoreDetailsLabel];
        
        m_pMoreDetailsTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleMoreDetailsTapped:)];
        [m_pMoreDetailsTapGestureRecognizer setDelegate:self];
        [self.pMoreDetailsLabel setUserInteractionEnabled:YES];
        [self.pMoreDetailsLabel setMultipleTouchEnabled:YES];
        [self.pMoreDetailsLabel addGestureRecognizer:m_pMoreDetailsTapGestureRecognizer];
        
        m_pProfileImageTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleProfileTapped:)];
        [m_pProfileImageTapGestureRecognizer setDelegate:self];
        [self.pUserImage addGestureRecognizer:m_pProfileImageTapGestureRecognizer];
        
        m_pBannerImageTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleProfileTapped:)];
        [m_pBannerImageTapGestureRecognizer setDelegate:self];
        [self.pBannerImage addGestureRecognizer:m_pBannerImageTapGestureRecognizer];
        
        m_pNameTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleProfileTapped:)];
        [m_pNameTapGestureRecognizer setDelegate:self];
        [self.pNameLabel addGestureRecognizer:m_pNameTapGestureRecognizer];
        
        m_pScreenNameTapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleProfileTapped:)];
        [m_pScreenNameTapGestureRecognizer setDelegate:self];
        [self.pScreenNameLabel addGestureRecognizer:m_pScreenNameTapGestureRecognizer];
        
        m_pImageStore = pImageStore;
    }
    return self;
}

- (void) dealloc
{
    [self clearImages];
    
    [self.pScreenNameLabel removeGestureRecognizer:m_pScreenNameTapGestureRecognizer];
    [m_pScreenNameTapGestureRecognizer release];
    m_pScreenNameTapGestureRecognizer = nil;
    
    [self.pNameLabel removeGestureRecognizer:m_pNameTapGestureRecognizer];
    [m_pNameTapGestureRecognizer release];
    m_pNameTapGestureRecognizer = nil;
    
    [self.pBannerImage removeGestureRecognizer:m_pBannerImageTapGestureRecognizer];
    [m_pBannerImageTapGestureRecognizer release];
    m_pBannerImageTapGestureRecognizer = nil;
    
    [self.pMoreDetailsLabel removeGestureRecognizer:m_pMoreDetailsTapGestureRecognizer];
    [m_pMoreDetailsTapGestureRecognizer release];
    m_pMoreDetailsTapGestureRecognizer = nil;

    [self.pMoreDetailsLabel removeFromSuperview];
    [self.pMoreDetailsLabel release];
    self.pMoreDetailsLabel = nil;
    
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
    
    [self.pTwitterBrandIcon removeFromSuperview];
    [self.pTwitterBrandIcon release];
    self.pTwitterBrandIcon = nil;
    
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
        
        [tweetContent addAttribute:NSLinkAttributeName value:arrLinkUrls[i]
                             range:NSMakeRange(startIndex, endIndex - startIndex + 1)];
    }
    
    [self.pTweetContent setAttributedText:tweetContent];
    
    [m_pImageStore loadImage:[strUserImagePath UTF8String]
                            :self.pUserImage
                            :^(UIImage* image)
                             {
                                 [self.pUserImage setImage:image];
                             }
                            :TwitterDefines::ProfileImageSize];
    
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
        [m_pProfileImageTapGestureRecognizer removeTarget:nil action:NULL];
        [m_pProfileImageTapGestureRecognizer addTarget:self action:@selector(handleTourChangeRequest:)];
    }
    else
    {
        [m_pProfileImageTapGestureRecognizer removeTarget:nil action:NULL];
        [m_pProfileImageTapGestureRecognizer addTarget:self action:@selector(handleProfileTapped:)];
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
    std::stringstream ss;
    ss << "https://twitter.com/" << [self.m_pScreenName UTF8String];
    
    m_pInterop->ShowExternalURL(ss.str());
}

- (void)handleTourChangeRequest:(UITapGestureRecognizer *)tap
{
    m_pInterop->OnChangeTourRequested([self.m_pUserName UTF8String]);
}

- (void) handleMoreDetailsTapped:(UITapGestureRecognizer *)tap
{
    std::stringstream ss;
    ss << "https://twitter.com/" << [self.m_pScreenName UTF8String] << "/status/" << [self.m_pTwitterId UTF8String];
    
    m_pInterop->ShowExternalURL(ss.str());
    
}

- (BOOL)textView:(UITextView *)textView shouldInteractWithURL:(NSURL *)url inRange:(NSRange)characterRange
{
    m_pInterop->ShowExternalURL([[url absoluteString] UTF8String]);
    
    return NO;
}

@end
