// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "UIButton+DefaultStates.h"

#include "ImageHelpers.h"
#include "UIColors.h"

@implementation UIButton (DefaultStates)

- (void)setDefaultStates
{
    [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(ExampleApp::Helpers::ColorPalette::ButtonPressColor)
                    forState:UIControlStateNormal];
    [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(ExampleApp::Helpers::ColorPalette::ButtonPressColorAlt)
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

- (void)setDefaultStatesWithImageNames:(NSString*)normalImageName
                                      :(NSString*)highlightImageName
{
  
    [self setDefaultStatesWithNormalImageName:normalImageName
                           highlightImageName:highlightImageName
                        normalBackgroundColor:ExampleApp::Helpers::ColorPalette::UiBackgroundColor
                     highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor];
}



- (void)setDefaultStatesWithNormalImageName:(NSString*)normalImageName
                             highlightImageName:(NSString*)highlightImageName
                            normalBackgroundColor:(UIColor *)normalColor
                            highlightBackgroundColor:(UIColor *)highlightColor
{
    
    
    [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(normalColor)
                    forState:UIControlStateNormal];
    [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(highlightColor)
                    forState:UIControlStateHighlighted];
    
    UIImage* normalImage = ExampleApp::Helpers::ImageHelpers::LoadImage(normalImageName);
    UIImage* highlightImage = ExampleApp::Helpers::ImageHelpers::LoadImage(highlightImageName);
    
    [self setImage:normalImage
          forState:UIControlStateNormal];
    [self setImage:highlightImage
          forState:UIControlStateHighlighted];
    
}

@end
