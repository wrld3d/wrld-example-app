// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinCreationDetailsViewInterop.h"
#include "CustomSwitch.h"
@class MyPinCreationDetailsView;



@interface MyPinCreationDetailsView : UIView <UINavigationControllerDelegate, UIImagePickerControllerDelegate, UITextViewDelegate, UITextFieldDelegate, UIPopoverControllerDelegate>
{
    ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewInterop* m_pInterop;
    UIViewController* m_pRootViewController;

    float m_stateChangeAnimationTimeSeconds;

    BOOL m_imageAttached;
    float m_maxImageWidth;

    BOOL m_usePopover;

    float m_controlContainerWidth;
    float m_controlContainerHeight;
    float m_scrollBoxPadding;

    float m_scrollContentBottomMargin;

    Byte* m_pImageDataBytes;
    size_t m_imageSize;
    BOOL m_hasNetworkConnectivity;

    int m_maxNumberOfCharactersInDescription;
}

- (id) initWithParams:(float)width :(float)height :(UIViewController*) rootViewController;

- (ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewInterop*)getInterop;

- (Byte*)getImageBuffer;
- (size_t)getImageSize;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (void) addDoneToolBarToKeyboard:(UITextView *)textView;


- (void) setHasNetworkConnectivity:(BOOL) hasNetworkConnectivity
    :(BOOL) shouldVerifyShareSettings;



@property (nonatomic, retain) UIView* pHeaderView;
@property (nonatomic, retain) UITextField* pTitleText;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pHeaderSeparator;


@property (nonatomic, retain) UIView* pBodyContainer;
@property (nonatomic, retain) UIScrollView* pBodyScrollView;

@property (nonatomic, retain) UITextView* pPoiDescriptionBox;
@property (nonatomic, retain) UILabel* pDescriptionPlaceholder;
@property (nonatomic, retain) UIImageView* pPoiImageView;
@property (nonatomic, retain) CustomSwitch* pShareSwitch;
@property (nonatomic, retain) UILabel* pShareLabel;
@property (nonatomic, retain) UIImageView* pShareImageView;
@property (nonatomic, retain) UIButton* pTermsButton;

@property (nonatomic, retain) UIView* pContentSeperator;
@property (nonatomic, retain) UIView* pFooterContainer;
@property (nonatomic, retain) UIButton* pCameraButton;
@property (nonatomic, retain) UIButton* pGalleryButton;
@property (nonatomic, retain) UIButton* pConfirmButton;

@property (nonatomic, retain) UIImage* pPlaceholderImage;

@end
