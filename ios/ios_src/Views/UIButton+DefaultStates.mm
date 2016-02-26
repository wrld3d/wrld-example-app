// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "UIButton+DefaultStates.h"

#include "ImageHelpers.h"
#include "UIColors.h"

@implementation UIButton (DefaultStates)

- (void)setDefaultStates
{
    [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(ExampleApp::Helpers::ColorPalette::UiBorderColor)
                    forState:UIControlStateNormal];
    [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(ExampleApp::Helpers::ColorPalette::ButtonPressColor)
                    forState:UIControlStateHighlighted];
}

- (void)setDefaultStatesWithImages:(UIImage*)normalImage
                                  :(UIImage*)highlightImage
{
    [self setImage:normalImage
          forState:UIControlStateNormal];
    [self setImage:highlightImage
          forState:UIControlStateHighlighted];
    
    [self setDefaultStates];
}

- (void)setDefaultStatesWithImageName:(NSString*)imageName
{
    UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(imageName);
    
    [self setDefaultStatesWithImages:image
                                    :image];
}

- (void)setDefaultStatesWithImageNames:(NSString*)normalImageName
                                      :(NSString*)highlightImageName
{
    UIImage* normalImage = ExampleApp::Helpers::ImageHelpers::LoadImage(normalImageName);
    UIImage* highlightImage = ExampleApp::Helpers::ImageHelpers::LoadImage(highlightImageName);
    
    [self setDefaultStatesWithImages:normalImage
                                    :highlightImage];
}

@end