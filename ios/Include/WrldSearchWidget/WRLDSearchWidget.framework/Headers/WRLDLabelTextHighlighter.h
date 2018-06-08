#pragma once

#include <UIKit/UIKit.h>

/*!
 Utility class used to highlight sections of a UILabel.
 */
@interface WRLDLabelTextHighlighter : NSObject

/*!
 Applies different attributs to a UILabel to highlight portions of the text.
 @param label The UILabel to assign the attributed text to.
 @param fullText The full text to assign to the UILabel.
 @param regularAttributes NSDictionary of UIFontDescription attributes to apply to non-highlighed portions of the fulltext.
 @param highlightText string to match the portions of the fulltext to be highlighted.
 @param highlightAttributes NSDictionary of UIFontDescription attributes to apply to highlighed portions of the fulltext.
 */
+ (void) applyAttributedTextTo: (UILabel*)label
                      fullText: (NSString*) fullText
             regularAttributes: (NSDictionary *) regularAttributes
                 highlightText: (NSString*) highlightText
           highlightAttributes: (NSDictionary*) highlightAttributes;

@end

