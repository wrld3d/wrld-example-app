#import "WidgetSearchResultTableViewCell.h"
#import <WRLDSearchWidget/WRLDLabelTextHighlighter.h>
#import "ImageHelpers.h"
#include "SearchWidgetView.h"

@interface WidgetSearchResultTableViewCell()
- (IBAction)navigationActionTriggered:(id)sender;
@property (nonatomic) IBOutlet UIButton *navigationButton;
@property (nonatomic) IBOutlet NSLayoutConstraint *navigationWidthConstraint;
@end

@implementation WidgetSearchResultTableViewCell
{
    id<WRLDSearchResultModel> m_currentResult;
    ExampleApp::SearchMenu::ISearchNavigationHandler* m_navigationHandler;
    CGFloat _navigationButtonWidth;
}

- (void) populateWith: (id<WRLDSearchResultModel>) searchResult fromQuery: (WRLDSearchQuery *) query
{
    m_currentResult = searchResult;
    [WRLDLabelTextHighlighter applyAttributedTextTo: self.titleLabel
                                           fullText: searchResult.title
                                  regularAttributes: self.titleLabelHighlightAttrs
                                      highlightText: query.queryString
                                highlightAttributes: self.titleLabelHighlightAttrs];

    [WRLDLabelTextHighlighter applyAttributedTextTo: self.descriptionLabel
                                           fullText: searchResult.subTitle
                                  regularAttributes: self.descriptionLabelRegularAttrs
                                      highlightText: query.queryString
                                highlightAttributes: self.descriptionLabelRegularAttrs];

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

- (void) setNavigationHidden:(BOOL) isNavigationHidden
{    
    self.navigationWidthConstraint.constant = isNavigationHidden ? 0 : _navigationButtonWidth;
    [self.navigationButton setHidden: isNavigationHidden];
}

- (void) assignNavigationHandler:(ExampleApp::SearchMenu::ISearchNavigationHandler *) navigationHandler
{
    m_navigationHandler = navigationHandler;
}

- (IBAction)navigationActionTriggered:(id)sender
{
    m_navigationHandler->NavigateTo(m_currentResult);
}

@end
