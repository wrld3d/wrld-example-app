// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>

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
        m_yCursor = 0.f;
        m_scrollBoxPadding = 5.f;

        m_pImageDataBytes = NULL;
        m_imageSize = 0;

        [self setFrame:CGRectMake(0, 0, width, height)];
        m_hasNetworkConnectivity = true;

        m_maxNumberOfCharactersInDescription = 10000;

        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pControlContainer];

        self.pTitleContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pControlContainer addSubview: self.pTitleContainer];

        self.pTitleImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_create_poi_off");
        [self.pTitleContainer addSubview: self.pTitleImage];

        self.pTitleText = [[[UITextField alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pTitleContainer addSubview: self.pTitleText];

        self.pBodyContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pControlContainer addSubview: self.pBodyContainer];

        self.pBodyScrollView = [[[UIScrollView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pBodyContainer addSubview: self.pBodyScrollView];

        self.pPoiDescriptionBox = [[[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pBodyScrollView addSubview: self.pPoiDescriptionBox];

        self.pDescriptionPlaceholder = [[[UILabel alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pPoiDescriptionBox addSubview: self.pDescriptionPlaceholder];

        self.pPoiImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pBodyScrollView addSubview: self.pPoiImage];

        self.pPlaceholderImage = ExampleApp::Helpers::ImageHelpers::LoadImage(@"image_blank");

        self.pCheckbox = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCheckbox.selected = m_hasNetworkConnectivity;
        [self.pCheckbox addTarget:self action:@selector(onCheckboxPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.pBodyContainer addSubview: self.pCheckbox];

        self.pShareLabel = [[[UILabel alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pBodyContainer addSubview: self.pShareLabel];

        self.pTermsLabel = [[[UILabel alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pBodyContainer addSubview: self.pTermsLabel];

        self.pFooterContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pControlContainer addSubview: self.pFooterContainer];

        self.pCloseButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pFooterContainer addSubview: self.pCloseButton];

        self.pCameraButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pFooterContainer addSubview: self.pCameraButton];

        self.pGalleryButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pFooterContainer addSubview: self.pGalleryButton];

        self.pConfirmButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pFooterContainer addSubview: self.pConfirmButton];

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

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver: self
     name: @"handlePause"
     object: nil];

    [self.pFooterContainer removeFromSuperview];
    [self.pFooterContainer release];

    [self.pBodyContainer removeFromSuperview];
    [self.pBodyContainer release];

    [self.pTitleText removeFromSuperview];
    [self.pTitleText release];

    [self.pTitleImage removeFromSuperview];
    [self.pTitleImage release];

    [self.pTitleContainer removeFromSuperview];
    [self.pTitleContainer release];

    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];

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

- (void)layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);

    m_scrollContentBottomMargin = 50;

    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyMultiplier = useFullScreenSize ? 0.9f : 0.6f;
    m_controlContainerWidth = floorf(boundsWidth * boundsOccupyMultiplier);
    m_controlContainerHeight = boundsHeight * boundsOccupyMultiplier;
    const float controlContainerX = (boundsWidth * 0.5f) - (m_controlContainerWidth * 0.5f);
    const float controlContainerY = (boundsHeight * 0.5f) - (m_controlContainerHeight * 0.5f);

    self.pControlContainer.frame = CGRectMake(controlContainerX, controlContainerY, m_controlContainerWidth, m_controlContainerHeight);
    self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;

    [self layoutHeader];
    [self layoutBody];
    [self layoutFooter];

    [self resizeImageViewToFit:self.pPlaceholderImage.size.width :self.pPlaceholderImage.size.height];
}

- (void) layoutHeader
{
    m_yCursor = 10.f;
    const float titleContainerWidth = m_controlContainerWidth;
    const float titleContainerHeight = 47.f;

    self.pTitleContainer.frame = CGRectMake(0, m_yCursor, titleContainerWidth, titleContainerHeight);
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;

    const float titleImageSize = 33.f;
    self.pTitleImage.frame = CGRectMake(12, 12, titleImageSize, titleImageSize);
    self.pTitleImage.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;

    const float textPadding = 22.f;
    const float titleTextX = titleImageSize + textPadding;
    self.pTitleText.frame = CGRectMake(titleTextX, 5, titleContainerWidth - titleTextX, titleContainerHeight);

    self.pTitleText.font = [UIFont systemFontOfSize:25.0f];
    self.pTitleText.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;

    if ([self.pTitleText respondsToSelector: @selector(setTintColor:)])
    {
        self.pTitleText.tintColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    }

    self.pTitleText.placeholder = @"Name your pin...";
    self.pTitleText.textAlignment = NSTextAlignmentLeft;
    self.pTitleText.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.pTitleText.returnKeyType = UIReturnKeyDone;
    [self.pTitleText setDelegate: self];

    m_yCursor += self.pTitleContainer.frame.size.height;
}

- (void) layoutBody
{
    const float bodyContainerY = m_yCursor;
    const float bodyContainerHeight = m_controlContainerHeight - (2.f * static_cast<float>(self.pTitleContainer.frame.size.height));

    self.pBodyContainer.frame = CGRectMake(0, bodyContainerY, m_controlContainerWidth, bodyContainerHeight);
    self.pBodyContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;

    const float shareBarY = 5.f;
    const float checkboxSize = 20.f;
    const float checkBoxX = 12.f;

    self.pCheckbox.frame = CGRectMake(checkBoxX, shareBarY + 5.f, checkboxSize, checkboxSize);
    [self.pCheckbox setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_checkbox_off") forState:UIControlStateNormal];
    [self.pCheckbox setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_checkbox_on") forState:UIControlStateSelected];

    const float shareLabelWidth = 45.f;
    const float shareLabelHeight = 30.f;
    const float shareLabelPadding = 12.f;
    const float shareLabelX = checkBoxX + checkboxSize + shareLabelPadding;

    self.pShareLabel.frame = CGRectMake(shareLabelX, shareBarY, shareLabelWidth, shareLabelHeight);
    self.pShareLabel.font = [UIFont italicSystemFontOfSize: 16.f];
    self.pShareLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    self.pShareLabel.text = @"Share";

    const float termsLabelWidth = 150.f;
    const float termsLabelHeight = 30.f;
    const float termsLabelX = shareLabelX + shareLabelWidth + 2.f;
    self.pTermsLabel.frame = CGRectMake(termsLabelX, shareBarY + 1.f, termsLabelWidth, termsLabelHeight);

    self.pTermsLabel.text = @"(Terms & Conditions)";
    self.pTermsLabel.font = [UIFont systemFontOfSize: 12.f];
    self.pTermsLabel.textAlignment = NSTextAlignmentLeft;
    self.pTermsLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextLinkColor;
    UITapGestureRecognizer* urlTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnLink:)];
    [self.pTermsLabel setUserInteractionEnabled:YES];
    [self.pTermsLabel addGestureRecognizer:urlTappedGesture];

    const float scrollViewY = shareBarY + checkboxSize + m_scrollBoxPadding;
    self.pBodyScrollView.frame = CGRectMake(0, scrollViewY, m_controlContainerWidth, bodyContainerHeight);

    const float poiDescriptionBoxX = 12.f;
    const float poiDescriptionBoxY = 24.f;
    const float poiDescriptionBoxHeight = 120.f;
    const float poiDescriptionBoxWidth = m_controlContainerWidth - (2 * poiDescriptionBoxX);
    self.pPoiDescriptionBox.frame = CGRectMake(poiDescriptionBoxX, poiDescriptionBoxY, poiDescriptionBoxWidth, poiDescriptionBoxHeight);
    self.pPoiDescriptionBox.font = [UIFont systemFontOfSize: 16.f];
    self.pPoiDescriptionBox.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    self.pPoiDescriptionBox.layer.cornerRadius = 8.f;
    self.pPoiDescriptionBox.layer.masksToBounds = YES;
    self.pPoiDescriptionBox.layer.borderColor = [ExampleApp::Helpers::ColorPalette::UiBorderColor CGColor];
    self.pPoiDescriptionBox.layer.borderWidth = 2.f;
    [self.pPoiDescriptionBox setDelegate: self];

    if(ExampleApp::Helpers::UIHelpers::UsePhoneLayout())
    {
        [self addDoneToolBarToKeyboard :self.pPoiDescriptionBox];
    }

    const float placeholderTextOffset = 8.f;
    self.pDescriptionPlaceholder.frame = CGRectMake(placeholderTextOffset, 2.f, poiDescriptionBoxWidth - placeholderTextOffset, 30.f);
    self.pDescriptionPlaceholder.hidden = NO;
    self.pDescriptionPlaceholder.font = [UIFont systemFontOfSize: 16.f];
    self.pDescriptionPlaceholder.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyLightColor;
    self.pDescriptionPlaceholder.text = @"Tell us about your pin...";

    const float poiImageY = poiDescriptionBoxHeight + poiDescriptionBoxY + 24.f;
    const float poiImageX = 12.f;
    m_maxImageWidth = m_controlContainerWidth - (2 * poiImageX);
    const float poiImageHeight = m_maxImageWidth * 0.75f;
    self.pPoiImage.frame = CGRectMake(poiImageX, poiImageY, m_maxImageWidth, poiImageHeight);
    self.pPoiImage.image = self.pPlaceholderImage;

    const float scrollHeight = poiDescriptionBoxHeight + poiImageHeight + m_scrollContentBottomMargin;
    self.pBodyScrollView.contentSize = CGSizeMake(m_controlContainerWidth, scrollHeight);

    m_yCursor += self.pBodyContainer.frame.size.height;
}

- (void) layoutFooter
{
    const float footerY = m_yCursor;
    const float footerHeight = 64.f;
    const float footerWidth = m_controlContainerWidth;

    self.pFooterContainer.frame = CGRectMake(0, footerY - footerHeight/2 + m_scrollBoxPadding, footerWidth, footerHeight);
    self.pFooterContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;

    const int numberOfButtons = 4;
    const float buttonSize = static_cast<float>(self.pFooterContainer.frame.size.height);
    const float buttonPadding = (m_controlContainerWidth - (numberOfButtons * buttonSize)) / (numberOfButtons + 1);

    const float closeButtonX = buttonPadding;
    self.pCloseButton.frame = CGRectMake(closeButtonX, 0, buttonSize, buttonSize);
    [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
    [self.pCloseButton addTarget:self action:@selector(onCloseButtonPressed:) forControlEvents:UIControlEventTouchUpInside];

    const float cameraButtonX = buttonSize + 2 * buttonPadding;
    self.pCameraButton.frame = CGRectMake(cameraButtonX, 0, buttonSize, buttonSize);
    [self.pCameraButton setDefaultStatesWithImageNames:@"button_photo_off" :@"button_photo_on"];
    [self.pCameraButton addTarget:self action:@selector(onCameraButtonPressed:) forControlEvents:UIControlEventTouchUpInside];

    const float galleryButtonX = 2 * buttonSize + 3 * buttonPadding;
    self.pGalleryButton.frame = CGRectMake(galleryButtonX, 0, buttonSize, buttonSize);
    [self.pGalleryButton setDefaultStatesWithImageNames:@"button_gallery_off" :@"button_gallery_on"];
    [self.pGalleryButton addTarget:self action:@selector(onGalleryButtonPressed:) forControlEvents:UIControlEventTouchUpInside];

    const float confirmButtonX = 3 * buttonSize + 4 * buttonPadding;
    self.pConfirmButton.frame = CGRectMake(confirmButtonX, 0, buttonSize, buttonSize);
    [self.pConfirmButton setDefaultStatesWithImageNames:@"button_ok_off" :@"button_ok_on"];
    [self.pConfirmButton addTarget:self action:@selector(onConfirmButtonPressed:) forControlEvents:UIControlEventTouchUpInside];

    m_popoverX = m_controlContainerWidth * 0.5f;
    m_popoverY = footerY;
}

- (void) resetView
{
    self.pTitleText.text = @"";
    self.pPoiDescriptionBox.text = @"";
    self.pDescriptionPlaceholder.hidden = NO;
    self.pPoiImage.image = self.pPlaceholderImage;

    [self resizeImageViewToFit:self.pPlaceholderImage.size.width :self.pPlaceholderImage.size.height];

    self.pCheckbox.selected = m_hasNetworkConnectivity;
    m_imageAttached = NO;
    [self.pBodyScrollView setContentOffset:
     CGPointMake(0, -self.pBodyScrollView.contentInset.top) animated:YES];
}

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
        self.pPopover = [[UIPopoverController alloc] initWithContentViewController:imagePicker];

        CGRect popoverRect = CGRectMake(m_popoverX, m_popoverY, 1.f, 1.f);

        [self.pPopover presentPopoverFromRect:popoverRect
         inView:self.pControlContainer
         permittedArrowDirections:UIPopoverArrowDirectionDown
         animated:YES];

        [self.pPopover setDelegate: self];
    }
    else
    {
        [m_pRootViewController presentViewController:imagePicker animated:YES completion:nil];
    }
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo
{
    self.pPoiImage.image = image;
    [self resizeImageViewToFit:image.size.width :image.size.height];

    m_imageAttached = YES;
    if(m_usePopover)
    {
        [self.pPopover dismissPopoverAnimated: YES];
    }
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    if(m_usePopover)
    {
        [self.pPopover dismissPopoverAnimated: YES];
    }
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void) onCloseButtonPressed:(UIButton *)sender
{
    m_pInterop->OnDismissed();
}

- (void) onCameraButtonPressed:(UIButton *)sender
{
    if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera] == NO)
    {
        UIAlertView* noCameraAlert = [[UIAlertView alloc] initWithTitle: @"No Camera!"
                                      message: @"This device has no available camera"
                                      delegate: nil
                                      cancelButtonTitle: @"Dismiss"
                                      otherButtonTitles: nil];

        [noCameraAlert show];
        [noCameraAlert release];
        return;
    }

    if ([self checkCameraPermissionsDisabled])
    {
        NSString* appName =  [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
        NSString* message = [NSString stringWithFormat: @"Please ensure %@ has camera access in your privacy settings", appName];
        UIAlertView* noPermissionsAlert = [[UIAlertView alloc] initWithTitle: @"Unable to access camera"
                                                                     message: message
                                                                    delegate: nil
                                                           cancelButtonTitle: @"Dismiss"
                                                           otherButtonTitles: nil];
        
        [noPermissionsAlert show];
        [noPermissionsAlert release];
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
    UIImage* imageToSend = m_imageAttached ? self.pPoiImage.image : nil;

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

- (BOOL)popoverControllerShouldDismissPopover:(UIPopoverController *)popoverController
{
    if(m_usePopover)
    {
        [self.pPopover dismissPopoverAnimated: YES];
    }
    return YES;
}

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

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
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

- (void) userTappedOnLink:(UITapGestureRecognizer *)recognizer
{
    NSString * webUrlString = @"http://wrld3d.com/tos";
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}

- (void) resizeImageViewToFit:(CGFloat)sourceImageWidth :(CGFloat)sourceImageHeight
{
    const CGFloat widthRatio = m_maxImageWidth/sourceImageWidth;
    const CGFloat height = sourceImageHeight * widthRatio;

    CGRect frame = self.pPoiImage.frame;
    self.pPoiImage.frame = CGRectMake(frame.origin.x, frame.origin.y, m_maxImageWidth, height);

    self.pBodyScrollView.contentSize = CGSizeMake(m_controlContainerWidth, self.pPoiImage.frame.origin.y + self.pPoiImage.frame.size.height + m_scrollContentBottomMargin);
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if(textField == self.pTitleText)
    {
        NSUInteger newLength  = [textField.text length] + [string length] - range.length;
        return (newLength <= 100);
    }
    else return YES;
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
        self.pCheckbox.selected = m_hasNetworkConnectivity;
    }
}

- (void) verifyShareSettingsValid
{
    if (self.pCheckbox.selected && !m_hasNetworkConnectivity)
    {
        UIAlertView* alert = [[[UIAlertView alloc] initWithTitle: @"No network connection"
                               message: @"Pins cannot be shared when no network connection is available"
                               delegate: nil
                               cancelButtonTitle: @"Dismiss"
                               otherButtonTitles: nil] autorelease];

        [alert show];
        self.pCheckbox.selected = NO;
    }
}

- (void)onPause
{
    if(m_usePopover)
    {
        [self.pPopover dismissPopoverAnimated: YES];
    }
    [m_pRootViewController dismissViewControllerAnimated:YES completion:nil];
}

- (BOOL) checkCameraPermissionsDisabled
{
    AVAuthorizationStatus authorizationStatus = [AVCaptureDevice authorizationStatusForMediaType: AVMediaTypeVideo];
    
    return authorizationStatus == AVAuthorizationStatusDenied ||
           authorizationStatus == AVAuthorizationStatusRestricted;
}

@end
