// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <WrldSearchWidget/WrldSearchWidget.h>

@interface SwallowSectionChild : WRLDMenuChild
@property (readonly) int section;
@property (readonly) int child;

- (instancetype)initWithText:(NSString *)text
                        icon:(NSString *)theIcon
                     section:(int)theSection
                       child:(int)theChild;
@end
@implementation SwallowSectionChild
- (instancetype)initWithText:(NSString *)text
                        icon:(NSString *)theIcon
                     section:(int)theSection
                       child:(int)theChild
{
    self = [super initWithText:text icon:theIcon context:NULL];
    if (self)
    {
        _section = theSection;
        _child   = theChild;
    }
    return self;
}
@end
