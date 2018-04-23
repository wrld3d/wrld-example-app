#pragma once

#include <UIKit/UIKit.h>

@interface WRLDLabelTextHighlighter : NSObject

+ (void) applyAttributedTextTo :(UILabel*)label
                       fullText:(NSString*) fullText
              regularAttributes:(NSDictionary *) regularAttributes
                       boldText:(NSString*) boldText
                 boldAttributes:(NSDictionary*) boldAttributes;

@end

