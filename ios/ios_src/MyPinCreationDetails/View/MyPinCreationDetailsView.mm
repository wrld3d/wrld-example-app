// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"
#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "ViewController.h"
#import "UIHelpers.h"
#import "UIButton+DefaultStates.h"

@implementation MyPinCreationDetailsView

- (id)initWithParams:(float)width :(float)height :(UIViewController*) rootViewController
{
    self = [super init];

    if(self)
    {
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_imageAttached = NO;

        m_pInterop = new ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewInterop(self);
        m_pRootViewController = rootViewController;

        m_controlContainerHeight = 0.f;
        m_controlContainerWidth = 0.f;
        
        m_scrollBoxPadding = 5.f;

        m_pImageDataBytes = NULL;
        m_imageSize = 0;

        [self setFrame:CGRectMake(0, 0, width, height)];
        m_hasNetworkConnectivity = true;

        m_maxNumberOfCharactersInDescription = 10000;

        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        [self setupHeader];
        [self setupBody];
        [self setupFooter];
        [self setDefaultText];
        
        m_usePopover = !ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
        
        [self layoutSubviews];
        [self setTouchExclusivity: self];

        [[NSNotificationCenter defaultCenter] addObserver: self
         selector: @selector(onPause)
         name: @"handlePause"
         object: nil];
    }

    return self;
}


- (void) setupHeader
{
    self.pHeaderView = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    [self addSubview: self.pHeaderView];
    
    self.pCloseButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pHeaderView addSubview: self.pCloseButton];
    
    [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
    
    [self.pCloseButton addTarget:self action:@selector(onCloseButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    self.pHeaderSeparator = [[[UIView alloc] init] autorelease];
    self.pHeaderSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
    [self addSubview:self.pHeaderSeparator];
    
    self.pTitleText = [[[UITextField alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    
    self.pTitleText.textAlignment = NSTextAlignmentLeft;
    self.pTitleText.returnKeyType = UIReturnKeyDone;
    [self.pTitleText setDelegate: self];
    [self.pHeaderView addSubview: self.pTitleText];
    
    self.pTitleText.font = [UIFont systemFontOfSize:24.0f];
    self.pTitleText.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    
    if ([self.pTitleText respondsToSelector: @selector(setTintColor:)])
    {
        self.pTitleText.tintColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    }
}

-(void)setupBody{
    self.pBodyScrollView = [[[UIScrollView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self addSubview: self.pBodyScrollView];
    
    self.pBodyContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pBodyScrollView addSubview: self.pBodyContainer];
    
    self.pPoiDescriptionBox = [[[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pBodyContainer addSubview: self.pPoiDescriptionBox];
    
    self.pPoiDescriptionBox.font = [UIFont systemFontOfSize: 16.f];
    self.pPoiDescriptionBox.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    self.pPoiDescriptionBox.layer.cornerRadius = 8.f;
    self.pPoiDescriptionBox.layer.masksToBounds = YES;
    self.pPoiDescriptionBox.layer.borderColor = [ExampleApp::Helpers::ColorPalette::UiBorderColor CGColor];
    self.pPoiDescriptionBox.layer.borderWidth = 2.f;
    [self.pPoiDescriptionBox setDelegate: self];
    
    if(ExampleApp::Helpers::UIHelpers::UsePhoneLayout())
    {
        [self addDoneToolBarToKeyboard:self.pPoiDescriptionBox];
    }
    
    self.pDescriptionPlaceholder = [[[UILabel alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pPoiDescriptionBox addSubview: self.pDescriptionPlaceholder];
    self.pDescriptionPlaceholder.font = [UIFont systemFontOfSize: 16.f];
    self.pDescriptionPlaceholder.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyLightColor;
   
    self.pDescriptionPlaceholder.hidden = NO;
    
    [self.pPoiDescriptionBox addSubview:self.pDescriptionPlaceholder];
    
    self.pPlaceholderImage = ExampleApp::Helpers::ImageHelpers::LoadImage(@"image_blank");
    self.pPoiImageView = [[UIImageView alloc] initWithImage:self.pPlaceholderImage];
    
    [self.pBodyContainer addSubview: self.pPoiImageView];

    UIImage *onImage =   [UIImage imageNamed:@"FullSwitchOn"];
    UIImage *offImage =  [UIImage imageNamed:@"FullSwitchOff"];
    self.pShareSwitch = [[[CustomSwitch alloc] initWithOnImage:onImage offImage:offImage] autorelease];
    [self.pShareSwitch setOn:m_hasNetworkConnectivity];
    
    [self.pShareSwitch addTarget:self action:@selector(onCheckboxPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.pBodyContainer addSubview: self.pShareSwitch];
    
    self.pShareLabel = [[[UILabel alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pBodyContainer addSubview: self.pShareLabel];
    
    self.pShareImageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"ShareIcon"]];
    [self.pBodyContainer addSubview:self.pShareImageView];
    
    self.pTermsButton = [[UIButton alloc] init];
    [self.pTermsButton setTitle:@"(Terms & Conditions)" forState:UIControlStateNormal];
    self.pTermsButton.titleLabel.text = @"(Terms & Conditions)";
    self.pTermsButton.titleLabel.font = [UIFont systemFontOfSize: 12.f];
    self.pTermsButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
    self.pTermsButton.titleLabel.textAlignment = NSTextAlignmentLeft;
    [self.pTermsButton setTitleColor:ExampleApp::Helpers::ColorPalette::UiTextLinkColor forState:UIControlStateNormal];
     
    self.pTermsButton.titleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextLinkColor;
    [self.pTermsButton addTarget:self action:@selector(userTappedOnLink:) forControlEvents:UIControlEventTouchUpInside];
   
    [self.pBodyContainer addSubview:self.pTermsButton];
    
    self.pShareLabel.font = [UIFont systemFontOfSize: 16.f];
    self.pShareLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    self.pShareLabel.text = @"Share";
    
}

-(void)setupFooter{
    
    self.pFooterContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    self.pFooterContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSubCellColor;
    [self addSubview: self.pFooterContainer];
    
    self.pContentSeperator= [[[UIView alloc] init] autorelease];
    self.pContentSeperator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
    [self.pFooterContainer addSubview:self.pContentSeperator];
    
    self.pCameraButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pFooterContainer addSubview: self.pCameraButton];
    
    self.pGalleryButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pFooterContainer addSubview: self.pGalleryButton];
    
    self.pConfirmButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pFooterContainer addSubview: self.pConfirmButton];
    
    [self.pCameraButton setDefaultStatesWithNormalImageName:@"ButtonPhoto"
                                         highlightImageName:@"ButtonPhoto_Down"
                                      normalBackgroundColor:UIColor.clearColor
                                   highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::UiBorderColor];
    
    [self.pCameraButton addTarget:self action:@selector(onCameraButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
   
    
    [self.pGalleryButton setDefaultStatesWithNormalImageName:@"ButtonGallery"
                                          highlightImageName:@"ButtonGallery_Down"
                                       normalBackgroundColor:UIColor.clearColor
                                    highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::UiBorderColor];
   
    [self.pGalleryButton addTarget:self action:@selector(onGalleryButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
   
    
    [self.pConfirmButton setDefaultStatesWithNormalImageName:@"LargeTick_Blue"
                                          highlightImageName:@"LargeTick_White"
                                       normalBackgroundColor:UIColor.clearColor
                                    highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::UiBorderColor];
     
     
   
    [self.pConfirmButton addTarget:self action:@selector(onConfirmButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
   
}




- (void)layoutSubviews
{
    UIViewController *viewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    self.frame = [viewController largePopoverFrame];
    
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(8.0, 8.0, 8.0, 8.0);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(16.0, 16.0, 16.0, 16.0);
    
    
    CGFloat innerMarginWidth = self.frame.size.width - innerMargin.left - innerMargin.right;
    CGFloat outerMarginWidth = self.frame.size.width - outerMargin.left - outerMargin.right;
    
    
    //layout header
    CGFloat headerHeight = 37;
    
    self.pHeaderView.frame = CGRectMake(innerMargin.left, outerMargin.top, innerMarginWidth,headerHeight );
    
    CGFloat centeringOffsetY = 4.0;
    self.pTitleText.frame = CGRectMake(0.0,centeringOffsetY, innerMarginWidth - headerHeight,headerHeight);
    
    self.pCloseButton.frame = CGRectMake(innerMarginWidth - headerHeight,0.0, headerHeight,headerHeight);
    
    self.pHeaderSeparator.frame = CGRectMake(outerMargin.left, self.pHeaderView.frame.origin.y + self.pHeaderView.frame.size.height + outerMargin.top, outerMarginWidth,1.0);
    
    CGFloat scrollViewyOffset = self.pHeaderSeparator.frame.origin.y + self.pHeaderSeparator.frame.size.height;
    
    CGFloat footerHeight = 66;
    
    //layout body
    self.pBodyScrollView.frame = CGRectMake(0.0,
                                               scrollViewyOffset,
                                               self.frame.size.width,
                                               self.frame.size.height - scrollViewyOffset - footerHeight);
    
    const float poiDescriptionBoxHeight = 120.f;
   

    self.pPoiDescriptionBox.frame = CGRectMake(innerMargin.left,
                                               innerMargin.top,
                                               innerMarginWidth,
                                               poiDescriptionBoxHeight);
    
    
    self.pDescriptionPlaceholder.frame = CGRectMake(outerMargin.left, outerMargin.top,innerMarginWidth - outerMargin.left -outerMargin.right, 20.f);
    
    CGSize imageSize = self.pPoiImageView.image.size;
    CGFloat aspectRatio = imageSize.height/imageSize.width;
    
    self.pPoiImageView.frame = CGRectMake(innerMargin.left,
                                               innerMargin.top + self.pPoiDescriptionBox.frame.size.height + self.pPoiDescriptionBox.frame.origin.y ,
                                               innerMarginWidth,
                                               innerMarginWidth*aspectRatio);
    
    CGFloat shareOffsetX =  innerMargin.right;
    CGFloat shareOffsetY =  self.pPoiImageView.frame.size.height +  self.pPoiImageView.frame.origin.y + innerMargin.top;
    CGSize shareImageSize = self.pShareImageView.frame.size;
    
    
    self.pShareImageView.frame = CGRectMake(shareOffsetX ,
                                            shareOffsetY ,
                                            shareImageSize.width,
                                            shareImageSize.height);
    
    self.pShareLabel.frame = CGRectMake( self.pShareImageView.frame.origin.x + shareImageSize.width + outerMargin.left,
                                        shareOffsetY,
                                        45,
                                        shareImageSize.height);
    
    
    CGFloat switchWidth = 40;
    self.pShareSwitch.frame = CGRectMake(self.frame.size.width - innerMargin.right - switchWidth,
                                      shareOffsetY,
                                      switchWidth,
                                      shareImageSize.height);
    
    
    CGFloat termsX = self.pShareLabel.frame.origin.x + self.pShareLabel.frame.size.width + outerMargin.left;
    self.pTermsButton.frame = CGRectMake(termsX,
                                         shareOffsetY,
                                         self.pShareSwitch.frame.origin.x - termsX - outerMargin.right,
                                         shareImageSize.height);
    
    
    self.pBodyContainer.frame = CGRectMake(0.0,
                                           0.0,
                                           self.frame.size.width,
                                           self.pShareLabel.frame.origin.y + self.pShareLabel.frame.size.height + innerMargin.top);
    
     self.pBodyScrollView.contentSize = self.pBodyContainer.frame.size;
    
    [self.pBodyScrollView setContentOffset:CGPointMake(0, -self.pBodyScrollView.contentInset.top) animated:NO];
    
    //layout footer
    self.pFooterContainer.frame = CGRectMake(0.0,
                                             self.pBodyScrollView.frame.origin.y + self.pBodyScrollView.frame.size.height,
                                             self.frame.size.width,
                                             footerHeight);
    
    
    
    self.pContentSeperator.frame = CGRectMake(0.0,0.0,self.frame.size.width,1.0);
    
    
    CGFloat buttonHeight = self.pFooterContainer.frame.size.height - 1;
    CGFloat buttonWidth = self.frame.size.width/3.0;
    
    self.pCameraButton.frame = CGRectMake(0.0, 1, buttonWidth, buttonHeight);
    
    self.pGalleryButton.frame = CGRectMake(buttonWidth, 1, buttonWidth, buttonHeight);
   
    self.pConfirmButton.frame = CGRectMake(2.0*buttonWidth, 1, buttonWidth, buttonHeight);
    
}


- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver: self
                                                    name: @"handlePause"
                                                  object: nil];
    
    [self.pTitleText removeFromSuperview];
    [self.pTitleText release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pHeaderSeparator removeFromSuperview];
    [self.pHeaderSeparator release];
    
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];

    [self.pPoiDescriptionBox removeFromSuperview];
    [self.pPoiDescriptionBox release];
    
    [self.pPoiImageView removeFromSuperview];
    [self.pPoiImageView release];
    
    [self.pDescriptionPlaceholder removeFromSuperview];
    [self.pDescriptionPlaceholder release];
    
    [self.pShareSwitch removeFromSuperview];
    [self.pShareSwitch release];
    
    [self.pShareLabel removeFromSuperview];
    [self.pShareLabel release];
    
    [self.pShareImageView removeFromSuperview];
    [self.pShareImageView release];
    
    [self.pTermsButton removeFromSuperview];
    [self.pTermsButton release];
    
    [self.pBodyContainer removeFromSuperview];
    [self.pBodyContainer release];
    
    [self.pBodyScrollView removeFromSuperview];
    [self.pBodyScrollView release];
    
    [self.pContentSeperator removeFromSuperview];
    [self.pContentSeperator release];
    
    [self.pCameraButton removeFromSuperview];
    [self.pCameraButton release];
    
    [self.pGalleryButton removeFromSuperview];
    [self.pGalleryButton release];
    
    [self.pConfirmButton removeFromSuperview];
    [self.pConfirmButton release];
    
    [self.pFooterContainer removeFromSuperview];
    [self.pFooterContainer release];
    
    [self.pPlaceholderImage release];
    
    delete m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

- (ExampleApp::MyPinCreationDetails::View::MyPinCreationDetailsViewInterop*)getInterop
{
    return m_pInterop;
}

- (Byte*)getImageBuffer
{
    return m_pImageDataBytes;
}

- (size_t)getImageSize;
{
    return m_imageSize;
}

-(void) setDefaultText {
    self.pTitleText.text = @"";
    self.pTitleText.placeholder = @"Name your pin...";
    self.pPoiDescriptionBox.text = @"";
    self.pDescriptionPlaceholder.text = @"Tell us about your pin...";
}

- (void) resetView
{
    self.pDescriptionPlaceholder.hidden = NO;
    self.pPoiImageView.image = self.pPlaceholderImage;
    [self setDefaultText];
    [self.pShareSwitch setOn:m_hasNetworkConnectivity];
    m_imageAttached = NO;
    [self setNeedsLayout];
}

- (void) setFullyActive
{
    if(self.alpha == 1.f)
    {
        return;
    }

    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    if(self.alpha == 0.f)
    {
        return;
    }

    [self animateToAlpha:0.f];
}

- (void) setActiveStateToIntermediateValue:(float)openState
{
    self.alpha = openState;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    return self.alpha > 0.f;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
     animations:^
    {
        self.alpha = alpha;
    }
    completion:^(BOOL finished)
    {
        if (self.alpha < 0.1f)
        {
            [self resetView];
        }
    }];
}



-(void)addDoneToolBarToKeyboard:(UITextView *)textView
{
    UIToolbar* doneToolbar = [[UIToolbar alloc]initWithFrame:CGRectMake(0, 0, 320, 50)];
    doneToolbar.barStyle = UIBarStyleBlackTranslucent;
    doneToolbar.items = [NSArray arrayWithObjects:
                         [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil],
                         [[UIBarButtonItem alloc]initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(doneButtonClickedDismissKeyboard)],
                         nil];
    [doneToolbar sizeToFit];
    textView.inputAccessoryView = doneToolbar;
}

-(void)doneButtonClickedDismissKeyboard
{
    [self.pPoiDescriptionBox resignFirstResponder];
}

- (void) setHasNetworkConnectivity: (BOOL) hasNetworkConnectivity
    : (BOOL) shouldVerifyShareSettings
{
    m_hasNetworkConnectivity = hasNetworkConnectivity;

    if (shouldVerifyShareSettings)
    {
        [self verifyShareSettingsValid];
    }
    else
    {
        [self.pShareSwitch setOn:m_hasNetworkConnectivity];
    }
}

- (void) verifyShareSettingsValid
{
    if (self.pShareSwitch.isOn && !m_hasNetworkConnectivity)
    {
        UIAlertController *alertController = ExampleApp::Helpers::UIHelpers::CreateSimpleAlert(@"No network connection",
                                                                                               @"Pins cannot be shared when no network connection is available",
                                                                                               @"Dismiss");
        [m_pRootViewController presentViewController:alertController animated:YES completion:nil];
        
        [self.pShareSwitch setOn:NO];
    }
}

- (void)onPause
{
    [m_pRootViewController dismissViewControllerAnimated:YES completion:nil];
}

- (BOOL) checkCameraPermissionsDisabled
{
    AVAuthorizationStatus authorizationStatus = [AVCaptureDevice authorizationStatusForMediaType: AVMediaTypeVideo];
    
    return authorizationStatus == AVAuthorizationStatusDenied ||
           authorizationStatus == AVAuthorizationStatusRestricted;
}

#pragma mark - Button Actions

- (void) onCheckboxPressed:(UIButton *) sender
{
    [sender setSelected:!sender.selected];
    [self verifyShareSettingsValid];
}

-(void) onGalleryButtonPressed:(UIButton *)sender
{
    UIImagePickerController *imagePicker = [[[UIImagePickerController alloc] init] autorelease];
    
    imagePicker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    imagePicker.delegate=self;
    imagePicker.allowsEditing = NO;
    if(m_usePopover)
    {
        imagePicker.modalPresentationStyle = UIModalPresentationPopover;
        UIPopoverPresentationController* ppc = [imagePicker popoverPresentationController];
        ppc.sourceView = self.pGalleryButton;
        ppc.sourceRect = CGRectMake(CGRectGetMidX(self.pGalleryButton.bounds), CGRectGetMidY(self.pGalleryButton.bounds),0,0);
    }
    
    [m_pRootViewController presentViewController:imagePicker animated:YES completion:nil];
}


- (void) onCloseButtonPressed:(UIButton *)sender
{
    m_pInterop->OnDismissed();
}

- (void) onCameraButtonPressed:(UIButton *)sender
{
    if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera] == NO)
    {
    
        UIAlertController *alertController = ExampleApp::Helpers::UIHelpers::CreateSimpleAlert(@"No Camera!",
                                                                                               @"This device has no available camera",
                                                                                               @"Dismiss");
        [m_pRootViewController presentViewController:alertController animated:YES completion:nil];
        return;
    }
    
    if ([self checkCameraPermissionsDisabled])
    {
        NSString* appName =  [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
        NSString* message = [NSString stringWithFormat: @"Please ensure %@ has camera access in your privacy settings", appName];
        UIAlertController *alertController = ExampleApp::Helpers::UIHelpers::CreateSimpleAlert(@"Unable to access camera",
                                                                                               message,
                                                                                               @"Dismiss");
        [m_pRootViewController presentViewController:alertController animated:YES completion:nil];
        return;
    }
    
    UIImagePickerController *imagePicker = [[[UIImagePickerController alloc] init] autorelease];
    
    imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
    imagePicker.delegate = self;
    imagePicker.allowsEditing = NO;
    imagePicker.showsCameraControls = YES;
    imagePicker.navigationBarHidden = YES;
    
    [m_pRootViewController presentViewController:imagePicker animated:YES completion:nil];
}

- (void) onConfirmButtonPressed:(UIButton *)sender
{
    UIImage* imageToSend = m_imageAttached ? self.pPoiImageView.image : nil;
    
    m_pImageDataBytes = NULL;
    m_imageSize = 0;
    
    if (imageToSend)
    {
        NSData* imageData = UIImageJPEGRepresentation(imageToSend, 0.9f);
        m_pImageDataBytes = (Byte*) [imageData bytes];
        m_imageSize = [imageData length] / sizeof(Byte);
    }
    
    m_pInterop->OnConfirmed();
}

- (void) userTappedOnLink:(UITapGestureRecognizer *)recognizer
{
    NSString * webUrlString = @"https://www.wrld3d.com/terms-of-service/";
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}

#pragma mark - UIUIImagePickerController Delegate

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo
{
    self.pPoiImageView.image = image;
    
    [self setNeedsLayout];
    
    m_imageAttached = YES;

    
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [picker dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - UITextView Delegate

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    self.pDescriptionPlaceholder.hidden = ([textView.text length] > 0);
}

- (void)textViewDidChange:(UITextView *)textView
{
    self.pDescriptionPlaceholder.hidden = ([textView.text length] > 0);
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    self.pDescriptionPlaceholder.hidden = ([textView.text length] > 0);
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range
 replacementText:(NSString *)text
{
    if (textView.text.length + (text.length - range.length) <= m_maxNumberOfCharactersInDescription)
    {
        return YES;
    }
    
    int remainingNumberOfCharactersInDescription = static_cast<int>(m_maxNumberOfCharactersInDescription - textView.text.length);
    NSString* partialText = [text substringToIndex: remainingNumberOfCharactersInDescription + range.length];
    
    NSMutableString* mutableDescriptionText = [NSMutableString stringWithFormat: @"%@", textView.text];
    [mutableDescriptionText replaceCharactersInRange: range withString: partialText];
    textView.text = mutableDescriptionText;
    
    return NO;
}

#pragma mark - UITextField Delegate

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if(textField == self.pTitleText)
    {
        NSUInteger newLength  = [textField.text length] + [string length] - range.length;
        return (newLength <= 100);
    }
    else return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}


@end
