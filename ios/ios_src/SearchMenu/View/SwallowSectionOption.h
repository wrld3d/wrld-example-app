// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <WrldSearchWidget/WrldSearchWidget.h>

@interface SwallowSectionOption : WRLDMenuOption
@property (readonly) int section;

- (instancetype)initWithText:(NSString *)text
                     section:(int)theSection;
@end
@implementation SwallowSectionOption
- (instancetype)initWithText:(NSString *)text
                     section:(int)theSection
{
    self = [super initWithText:text context:NULL];
    if (self)
    {
        _section = theSection;
    }
    return self;
}
@end
