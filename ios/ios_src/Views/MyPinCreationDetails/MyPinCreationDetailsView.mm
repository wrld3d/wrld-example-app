// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "App.h"
#import <QuartzCore/QuartzCore.h>

@implementation MyPinCreationDetailsView

- (id)initWithController:(MyPinCreationDetailsViewController*)controller
{
    self = [super init];
    
    if(self)
    {
        m_pController = controller;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2;
        m_imageAttached = NO;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pControlContainer];
        
        self.pTitleContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pControlContainer addSubview: self.pTitleContainer];
        
        self.pTitleImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleImage.image = [UIImage imageNamed: @"button_create_poi.png"];
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
        
        self.pPlaceholderImage = [[[UIImage alloc] init] autorelease];
        self.pPlaceholderImage = [UIImage imageNamed: @"image_blank.png"];
        
        self.pCheckbox = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
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
        
        m_usePopover = !App::IsDevicePhone();
        
        [self layoutSubviews];
    }
    
    return self;
}

- (void)dealloc
{
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
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    const float boundsWidth = self.superview.bounds.size.width;
    const float boundsHeight = self.superview.bounds.size.height;
    
    m_scrollContentBottomMargin = 50;

    const bool useFullScreenSize = (boundsHeight < 600.f || boundsWidth < 400.f);
    const float boundsOccupyMultiplier = useFullScreenSize ? 0.9f : 0.6f;
    const float controlContainerWidth = floorf(boundsWidth * boundsOccupyMultiplier);
    const float controlContainerHeight = boundsHeight * boundsOccupyMultiplier;
    const float controlContainerX = (boundsWidth * 0.5f) - (controlContainerWidth * 0.5f);
    const float controlContainerY = (boundsHeight * 0.5f) - (controlContainerHeight * 0.5f);

    self.pControlContainer.frame = CGRectMake(controlContainerX, controlContainerY, controlContainerWidth, controlContainerHeight);
    self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    
    const float titleContainerY = 10.f;
    const float titleContainerWidth = controlContainerWidth;
    const float titleContainerHeight = 70.f;
    
    self.pTitleContainer.frame = CGRectMake(0, titleContainerY, titleContainerWidth, titleContainerHeight);
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
    
    const float titleImageWidth = 70.f;
    const float titleImageHeight = titleImageWidth;
    self.pTitleImage.frame = CGRectMake(0, 0, titleImageWidth, titleImageHeight);
    self.pTitleImage.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    
    const float textPadding = 10.f;
    const float titleTextX = titleImageWidth + textPadding;
    self.pTitleText.frame = CGRectMake(titleTextX, 0, titleContainerWidth - titleTextX, titleContainerHeight);
    
    self.pTitleText.font = [UIFont systemFontOfSize:25.0f];
    self.pTitleText.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    self.pTitleText.placeholder = @"Name your pin...";
    self.pTitleText.textAlignment = NSTextAlignmentLeft;
    self.pTitleText.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.pTitleText.clearsOnBeginEditing = YES;
    self.pTitleText.returnKeyType = UIReturnKeyDone;
    [self.pTitleText setDelegate: self];
    
    const float bodyContainerY = titleContainerY + titleContainerHeight;
    const float bodyContainerHeight = controlContainerHeight - (2 * titleImageHeight);
    const float bodyContainerWidth = controlContainerWidth;
    
    self.pBodyContainer.frame = CGRectMake(0, bodyContainerY, bodyContainerWidth, bodyContainerHeight);
    self.pBodyContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
    self.pBodyScrollView.frame = CGRectMake(0, 0, bodyContainerWidth, bodyContainerHeight - 30.f);
    
    const float poiDescriptionBoxX = 20.f;
    const float poiDescriptionBoxY = 20.f;
    const float poiDescriptionBoxHeight = 120.f;
    const float poiDescriptionBoxWidth = bodyContainerWidth - (2 * poiDescriptionBoxX);
    self.pPoiDescriptionBox.frame = CGRectMake(poiDescriptionBoxX, poiDescriptionBoxY, poiDescriptionBoxWidth, poiDescriptionBoxHeight);
    self.pPoiDescriptionBox.font = [UIFont systemFontOfSize: 16.f];
    self.pPoiDescriptionBox.layer.cornerRadius = 8.f;
    self.pPoiDescriptionBox.layer.masksToBounds = YES;
    self.pPoiDescriptionBox.layer.borderColor = [ExampleApp::Helpers::ColorPalette::GoldTone CGColor];
    self.pPoiDescriptionBox.layer.borderWidth = 2.f;
    [self.pPoiDescriptionBox setDelegate: self];
    
    if(App::IsDevicePhone())
    {
        [self addDoneToolBarToKeyboard :self.pPoiDescriptionBox];
    }
    
    const float placeholderTextOffset = 8.f;
    self.pDescriptionPlaceholder.frame = CGRectMake(placeholderTextOffset, 2.f, poiDescriptionBoxWidth - placeholderTextOffset, 30.f);
    self.pDescriptionPlaceholder.hidden = NO;
    self.pDescriptionPlaceholder.font = [UIFont systemFontOfSize: 16.f];
    self.pDescriptionPlaceholder.textColor = ExampleApp::Helpers::ColorPalette::GreyTone;
    self.pDescriptionPlaceholder.text = @"Tell us about your Point of Interest...";
    
    const float poiImageY = poiDescriptionBoxHeight + poiDescriptionBoxY + 30.f;
    const float poiImageX = 20.f;
    m_scrollContentWidth = bodyContainerWidth;
    m_maxImageWidth = bodyContainerWidth - (2 * poiImageX);
    const float poiImageHeight = m_maxImageWidth * 0.75f;
    self.pPoiImage.frame = CGRectMake(poiImageX, poiImageY, m_maxImageWidth, poiImageHeight);
    self.pPoiImage.image = self.pPlaceholderImage;
    
    const float scrollHeight = poiDescriptionBoxHeight + poiImageHeight + m_scrollContentBottomMargin;
    self.pBodyScrollView.contentSize = CGSizeMake(m_scrollContentWidth, scrollHeight);
    
    const float shadowHeight = 10.f;
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pBodyContainer, "shadow_03", 0.f, 0.f, bodyContainerWidth, shadowHeight);
    const float footerY = bodyContainerY + bodyContainerHeight;
    const float footerHeight = 70.f;
    const float footerWidth = controlContainerWidth;
    
    const float checkBoxWidth = 30.f;
    const float checkBoxHeight = checkBoxWidth;
    const float checkBoxX = 20.f;
    const float checkBoxY = bodyContainerHeight - checkBoxHeight;
    self.pCheckbox.frame = CGRectMake(checkBoxX, checkBoxY, checkBoxWidth, checkBoxHeight);
    [self.pCheckbox setBackgroundImage:[UIImage imageNamed:@"button_checkbox_off.png"] forState:UIControlStateNormal];
    [self.pCheckbox setBackgroundImage:[UIImage imageNamed:@"button_checkbox_on.png"] forState:UIControlStateSelected];
    self.pCheckbox.selected = YES;
    [self.pCheckbox addTarget:self action:@selector(onCheckboxPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    const float shareLabelWidth = 100.f;
    const float shareLabelHeight = 30.f;
    const float shareLabelX = checkBoxX + checkBoxWidth + 5.f;
    const float shareLabelY = bodyContainerHeight - shareLabelHeight;

    self.pShareLabel.frame = CGRectMake(shareLabelX, shareLabelY, shareLabelWidth, shareLabelHeight);
    self.pShareLabel.font = [UIFont italicSystemFontOfSize: 16.f];
    self.pShareLabel.textColor = ExampleApp::Helpers::ColorPalette::GreyTone;
    self.pShareLabel.text = @"Share";
    
    const float termsLabelWidth = 150.f;
    const float termsLabelHeight = 30.f;
    const float termsLabelX = bodyContainerWidth - 20.f - termsLabelWidth;
    const float termsLabelY = bodyContainerHeight - termsLabelHeight;
    self.pTermsLabel.frame = CGRectMake(termsLabelX, termsLabelY, termsLabelWidth, termsLabelHeight);
    self.pTermsLabel.text = @"Terms & Conditions";
    self.pTermsLabel.font = [UIFont systemFontOfSize: 16.f];
    self.pTermsLabel.textAlignment = NSTextAlignmentRight;
    self.pTermsLabel.textColor = ExampleApp::Helpers::ColorPalette::LinkTone;
    UITapGestureRecognizer* urlTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnLink:)];
    [self.pTermsLabel setUserInteractionEnabled:YES];
    [self.pTermsLabel addGestureRecognizer:urlTappedGesture];
    
    self.pFooterContainer.frame = CGRectMake(0, footerY, footerWidth, footerHeight);
    self.pFooterContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pFooterContainer, "shadow_03", 0.f, 0.f, bodyContainerWidth, shadowHeight);
    
    const int numberOfButtons = 4;
    const float buttonWidth = 70.f;
    const float buttonHeight = footerHeight;
    const float buttonPadding = (controlContainerWidth - (numberOfButtons * buttonWidth)) / (numberOfButtons + 1);
    
    const float closeButtonX = buttonPadding;
    self.pCloseButton.frame = CGRectMake(closeButtonX, 0, buttonWidth, buttonHeight);
    [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
    [self.pCloseButton addTarget:self action:@selector(onCloseButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    const float cameraButtonX = buttonWidth + 2 * buttonPadding;
    self.pCameraButton.frame = CGRectMake(cameraButtonX, 0, buttonWidth, buttonHeight);
    [self.pCameraButton setBackgroundImage:[UIImage imageNamed:@"button_photo.png"] forState:UIControlStateNormal];
    [self.pCameraButton addTarget:self action:@selector(onCameraButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    const float galleryButtonX = 2 * buttonWidth + 3 * buttonPadding;
    self.pGalleryButton.frame = CGRectMake(galleryButtonX, 0, buttonWidth, buttonHeight);
    [self.pGalleryButton setBackgroundImage:[UIImage imageNamed:@"button_gallery.png"] forState:UIControlStateNormal];
    [self.pGalleryButton addTarget:self action:@selector(onGalleryButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    const float confirmButtonX = 3 * buttonWidth + 4 * buttonPadding;
    self.pConfirmButton.frame = CGRectMake(confirmButtonX, 0, buttonWidth, buttonHeight);
    [self.pConfirmButton setBackgroundImage:[UIImage imageNamed:@"button_ok.png"] forState:UIControlStateNormal];
    [self.pConfirmButton addTarget:self action:@selector(onConfirmButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    
    m_popoverX = bodyContainerWidth * 0.5f;
    m_popoverY = footerY;
    
    [self resizeImageViewToFit:self.pPlaceholderImage.size.width :self.pPlaceholderImage.size.height];
    [self setTouchExclusivity: self];
}

- (void) setTouchExclusivity: (UIView*) view
{
    for (UIView *subView in [view subviews])
    {
        if ([subView subviews] != nil)
        {
            [self setTouchExclusivity: subView];
        }

        subView.exclusiveTouch = YES;
    }
}

- (void) resetView
{
    self.pTitleText.text = @"";
    self.pPoiDescriptionBox.text = @"";
    self.pDescriptionPlaceholder.hidden = NO;
    self.pPoiImage.image = self.pPlaceholderImage;
    
    [self resizeImageViewToFit:self.pPlaceholderImage.size.width :self.pPlaceholderImage.size.height];
    
    self.pCheckbox.selected = YES;
    m_imageAttached = NO;
    [self.pBodyScrollView setContentOffset:
     CGPointMake(0, -self.pBodyScrollView.contentInset.top) animated:YES];
}

- (void) onCheckboxPressed:(UIButton *) sender
{
    [sender setSelected:!sender.selected];
}

-(void) onGalleryButtonPressed:(UIButton *)sender
{
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    
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
        [m_pController presentViewController:imagePicker animated:YES completion:nil];
    }
    
    [self prohibitScreenRotations];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)image editingInfo:(NSDictionary *)editingInfo
{
    [self reinstateScreenRotations];
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
    [self reinstateScreenRotations];
    
    if(m_usePopover)
    {
        [self.pPopover dismissPopoverAnimated: YES];
    }
    [picker dismissViewControllerAnimated:YES completion:nil];
}

- (void) onCloseButtonPressed:(UIButton *)sender
{
    [m_pController handleClosedButtonPressed];
}

- (void) prohibitScreenRotations
{
    UIDevice* currentDevice = [UIDevice currentDevice];
    
    while ([currentDevice isGeneratingDeviceOrientationNotifications])
    {
        [currentDevice endGeneratingDeviceOrientationNotifications];
    }
}

- (void) reinstateScreenRotations
{
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
}

- (void) onCameraButtonPressed:(UIButton *)sender
{
    [self prohibitScreenRotations];
    
    if ([UIImagePickerController isSourceTypeAvailable: UIImagePickerControllerSourceTypeCamera] == NO)
    {
        UIAlertView* noCameraAlert = [[UIAlertView alloc] initWithTitle: @"No Camera!"
                                                                message: @"This device has no available camera"
                                                               delegate: nil
                                                      cancelButtonTitle: @"Dismiss"
                                                      otherButtonTitles: nil];
        
        [noCameraAlert show];
        return;
    }
    
    
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    

    imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
    imagePicker.delegate = self;
    imagePicker.allowsEditing = NO;
    imagePicker.showsCameraControls = YES;
    imagePicker.navigationBarHidden = YES;
    
    [m_pController presentViewController:imagePicker animated:YES completion:nil];
}

- (void) onConfirmButtonPressed:(UIButton *)sender
{
    UIImage* imageToSend = m_imageAttached ? self.pPoiImage.image : nil;
    
    [m_pController handleConfirmButtonPressed : self.pTitleText.text
                                              : self.pPoiDescriptionBox.text
                                              : imageToSend
                                              : self.pCheckbox.selected];
}

- (BOOL)popoverControllerShouldDismissPopover:(UIPopoverController *)popoverController
{
    if(m_usePopover)
    {
        [self.pPopover dismissPopoverAnimated: YES];
    }
    [self reinstateScreenRotations];
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
                     animations:^{
                         self.alpha = alpha;
                     }
                     completion:^(BOOL finished){
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
    NSString * webUrlString = @"http://sdk.eegeo.com";
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}

- (void) resizeImageViewToFit:(float)sourceImageWidth :(float)sourceImageHeight
{
    const float widthRatio = m_maxImageWidth/sourceImageWidth;
    const float height = sourceImageHeight * widthRatio;
    
    CGRect frame = self.pPoiImage.frame;
    self.pPoiImage.frame = CGRectMake(frame.origin.x, frame.origin.y, m_maxImageWidth, height);
    
    self.pBodyScrollView.contentSize = CGSizeMake(m_scrollContentWidth, self.pPoiImage.frame.origin.y + self.pPoiImage.frame.size.height + m_scrollContentBottomMargin);
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

@end
