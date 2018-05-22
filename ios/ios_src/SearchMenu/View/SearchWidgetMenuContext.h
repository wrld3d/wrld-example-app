#pragma once

#import <Foundation/Foundation.h>

@interface SearchWidgetMenuContext : NSObject
@property (nonatomic, strong) NSString* menuText;
@property (nonatomic) NSInteger sectionIndex;
@property (nonatomic) NSInteger itemIndex;
@end
