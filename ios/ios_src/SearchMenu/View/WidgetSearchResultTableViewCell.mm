#import "WidgetSearchResultTableViewCell.h"
#import <WRLDSearchWidget/WRLDLabelTextHighlighter.h>
#import "ImageHelpers.h"

@implementation WidgetSearchResultTableViewCell
{
}

- (void) populateWith: (id<WRLDSearchResultModel>) searchResult fromQuery: (WRLDSearchQuery *) query
{
    [WRLDLabelTextHighlighter applyAttributedTextTo: self.titleLabel
                                           fullText: searchResult.title
                                  regularAttributes: self.titleLabelRegularAttrs
                                      highlightText: query.queryString
                                highlightAttributes: self.titleLabelHighlightAttrs];

    [WRLDLabelTextHighlighter applyAttributedTextTo: self.descriptionLabel
                                           fullText: searchResult.subTitle
                                  regularAttributes: self.descriptionLabelRegularAttrs
                                      highlightText: query.queryString
                                highlightAttributes: self.descriptionLabelHighlightAttrs];

    if(self.iconImageView && searchResult.iconKey)
    {
        std::string extendedIconKey = [[@"icon1_" stringByAppendingString:searchResult.iconKey] cStringUsingEncoding: NSUTF8StringEncoding];
        self.iconImageView.image = ExampleApp::Helpers::ImageHelpers::LoadImage(extendedIconKey);
    }
}

 - (void) prepareForReuse
{
    [super prepareForReuse];
    
    std::string extendedIconKey = "icon1_pin";
    self.iconImageView.image = ExampleApp::Helpers::ImageHelpers::LoadImage(extendedIconKey);
}

@end
