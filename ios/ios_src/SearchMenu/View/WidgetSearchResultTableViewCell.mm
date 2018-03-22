#import "WidgetSearchResultTableViewCell.h"
#import "ImageHelpers.h"

@implementation WidgetSearchResultTableViewCell
{
}

- (void) populateWith: (id<WRLDSearchResultModel>) searchResult fromQuery: (WRLDSearchQuery *) query
{
    [WRLDLabelTextHighlighter applyAttributedTextTo: self.titleLabel
                                           fullText: searchResult.title
                                  regularAttributes: self.titleLabelRegularAttrs
                                           boldText: query.queryString
                                     boldAttributes: self.titleLabelBoldAttrs];

    [WRLDLabelTextHighlighter applyAttributedTextTo: self.descriptionLabel
                                           fullText: searchResult.subTitle
                                  regularAttributes: self.descriptionLabelRegularAttrs
                                           boldText: query.queryString
                                     boldAttributes: self.descriptionLabelBoldAttrs];

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
