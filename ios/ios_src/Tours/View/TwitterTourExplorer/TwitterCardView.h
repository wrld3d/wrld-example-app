// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import "FXImageView.h"
#include "TourExplorerViewIncludes.h"

@class TwitterCardView;
@class ImageStore;

@interface TwitterCardView : UIView <UIGestureRecognizerDelegate, UITextViewDelegate>
{
    UITapGestureRecognizer* m_pMoreDetailsTapGestureRecognizer;
    UITapGestureRecognizer* m_pProfileImageTapGestureRecognizer;
    UITapGestureRecognizer* m_pBannerImageTapGestureRecognizer;
    UITapGestureRecognizer* m_pNameTapGestureRecognizer;
    UITapGestureRecognizer* m_pScreenNameTapGestureRecognizer;
    ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop* m_pInterop;
    ImageStore* m_pImageStore;
}

// @property ADD OUTLETS
@property (nonatomic, retain) IBOutlet UILabel* pNameLabel;
@property (nonatomic, retain) IBOutlet UILabel* pScreenNameLabel;
@property (nonatomic, retain) IBOutlet UILabel* pTimeStampLabel;
@property (nonatomic, retain) IBOutlet UIView* pUserImageContainer;
@property (nonatomic, retain) IBOutlet FXImageView* pUserImage;
@property (nonatomic, retain) IBOutlet FXImageView* pBannerImage;
@property (nonatomic, retain) IBOutlet FXImageView* pTwitterBrandIcon;
@property (nonatomic, retain) IBOutlet UITextView* pTweetContent;
@property (nonatomic, retain) IBOutlet UILabel* pMoreDetailsLabel;

@property (nonatomic, retain) NSString* m_pTwitterId;
@property (nonatomic, retain) NSString* m_pUserName;
@property (nonatomic, retain) NSString* m_pScreenName;

- (id) initWithParams:(ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop*)pInterop :(ImageStore*)pImageStore;

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
    linkEndIndices:(NSMutableArray*)arrLinkEndIndices;

- (void) clearImages;

- (void) handleMoreDetailsTapped:(UITapGestureRecognizer *)tap;

@end
