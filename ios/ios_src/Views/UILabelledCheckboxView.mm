// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "UILabelledCheckboxView.h"
#include "UIColors.h"
#include "ImageHelpers.h"

@implementation UILabelledCheckboxView

- (id) initWithParams:(float)checkboxSize
                     :(const char*)checkedAsset
                     :(const char*)uncheckedAsset
                     :(const char*)labelContents
                     :(bool)initiallySelected
                     :(id)clickHandlerInstance
                     :(SEL)clickHandler
{
    self = [super init];
    
    if(self)
    {
        self->pClickHandler = clickHandler;
        self->pClickHandlerInstance = clickHandlerInstance;
        
        self.pCheckbox = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, checkboxSize, checkboxSize)] autorelease];
        self.pCheckbox.selected = initiallySelected;
        [self addSubview:self.pCheckbox];
        [self.pCheckbox addTarget:self action:@selector(onCheckboxPressed:) forControlEvents:UIControlEventTouchUpInside];
        
        const float labelX = (checkboxSize + 5.f);
        self.pLabel = [[[UILabel alloc] initWithFrame: CGRectMake(labelX, 0.f, 0.f, checkboxSize)] autorelease];
        [self addSubview:self.pLabel];
        
        [self.pCheckbox setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(checkedAsset) forState:UIControlStateNormal];
        [self.pCheckbox setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(uncheckedAsset) forState:UIControlStateSelected];
        
        self.pLabel.font = [UIFont systemFontOfSize: 16.f];
        self.pLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pLabel.text = [NSString stringWithUTF8String:labelContents];
        [self.pLabel sizeToFit];
        
        const float centredLabelHeight = static_cast<float>((checkboxSize/2.f) - (self.pLabel.frame.size.height / 2.f));
        CGRect f = self.pLabel.frame;
        f.origin.y = centredLabelHeight;
        self.pLabel.frame = f;
        
        self.frame = CGRectMake(0.f, 0.f, self.pCheckbox.frame.size.width + self.pLabel.frame.size.width, checkboxSize);
        [self addTarget:self action:@selector(onCheckboxPressed:) forControlEvents:UIControlEventTouchUpInside];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pCheckbox removeFromSuperview];
    [self.pCheckbox release];
    
    [self.pLabel removeFromSuperview];
    [self.pLabel release];
    
    [super dealloc];
}

- (bool) isSelected
{
    return self.pCheckbox.selected;
}

- (void) setVisualSelectionState:(bool)selected
{
    [self.pCheckbox setSelected:selected];
}

- (void) onCheckboxPressed:(UIButton *) sender
{
    [self.pCheckbox setSelected:!self.pCheckbox.selected];
    [self->pClickHandlerInstance performSelector:self->pClickHandler];
}

@end