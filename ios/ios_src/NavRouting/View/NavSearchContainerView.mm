#import <Foundation/Foundation.h>

#import "NavSearchContainerView.h"
#import <WrldSearchWidget/WrldSearchWidget.h>

@interface NavSearchContainerView()
- (BOOL) consumesTouch:(UITouch *)touch;
- (void) setVisible:(BOOL) isVisible;
@end

@implementation NavSearchContainerView
{
    WRLDSearchWidgetView* m_pSearchView;
    UIView* m_pBackButton;
    UIView* m_pSearchHintContainer;
}

- (instancetype) initWithSubviews: (WRLDSearchWidgetView*) searchView :(UIView*) backButton :(UIView*) searchHintContainer
{
    CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ?
    CGRectMake(20, -50, 375, 300) :   // ipad
    CGRectMake(10, -50, CGRectGetWidth([[UIScreen mainScreen] bounds]) - 20, 300); // iphone
    
    if(self == [super initWithFrame:searchFrame])
    {
        m_pSearchView = searchView;
        m_pBackButton = backButton;
        m_pSearchHintContainer = searchHintContainer;
        
        [self addSubview: m_pSearchView];
        [self addSubview: m_pBackButton];
        [self addSubview: m_pSearchHintContainer];
        [self setHidden:YES];
        [self constrainSubviews];
    }
    return self;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    BOOL consume =  [m_pSearchView pointInside:[touch locationInView:m_pSearchView] withEvent:nil] ||
                    [m_pBackButton pointInside:[touch locationInView:m_pBackButton] withEvent:nil];
    return consume;
}

- (void) setVisible:(BOOL) isVisible
{
    [self setHidden: !isVisible];
}

-(void) constrainSubviews
{
    m_pSearchView.translatesAutoresizingMaskIntoConstraints = false;
    m_pBackButton.translatesAutoresizingMaskIntoConstraints = false;
    
    NSLayoutConstraint* searchTop = [self constrainAttribute: NSLayoutAttributeTop of: m_pSearchView to: self withOffset: 0];
    NSLayoutConstraint* searchBottom = [self constrainAttribute: NSLayoutAttributeBottom of: m_pSearchView to: self withOffset: 0];
    NSLayoutConstraint* searchLeading = [self constrainAttribute: NSLayoutAttributeLeading of: m_pSearchView to: self withOffset: 40];
    NSLayoutConstraint* searchTrailing = [self constrainAttribute: NSLayoutAttributeTrailing of: m_pSearchView to: self withOffset: 0];
    
    NSLayoutConstraint* backTop = [self constrainAttribute: NSLayoutAttributeTop of: m_pBackButton to: m_pSearchView withOffset: 0];
    NSLayoutConstraint* backHeight = [NSLayoutConstraint constraintWithItem:m_pBackButton
                                                                  attribute:NSLayoutAttributeBottom
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:m_pSearchView.suggestionsContainer
                                                                  attribute:NSLayoutAttributeTop
                                                                 multiplier:1.0
                                                                   constant:0];
    
    NSLayoutConstraint* backLeading = [self constrainAttribute: NSLayoutAttributeLeading of: m_pBackButton to: self withOffset: 0];
    NSLayoutConstraint* backTrailing = [NSLayoutConstraint constraintWithItem:m_pBackButton
                                                                    attribute:NSLayoutAttributeTrailing
                                                                    relatedBy:NSLayoutRelationEqual
                                                                       toItem:m_pSearchView
                                                                    attribute:NSLayoutAttributeLeading
                                                                   multiplier:1.0
                                                                     constant:0];
    
    [self addConstraint:searchTop];
    [self addConstraint:searchBottom];
    [self addConstraint:searchLeading];
    [self addConstraint:searchTrailing];
    
    [self addConstraint:backTop];
    [self addConstraint:backHeight];
    [self addConstraint:backLeading];
    [self addConstraint:backTrailing];
}

-(NSLayoutConstraint*) constrainAttribute: (NSLayoutAttribute)attribute of:(UIView*) constrained to:(UIView*) constrainer withOffset: (CGFloat) constant
{
    return [NSLayoutConstraint constraintWithItem:constrained
                                        attribute:attribute
                                        relatedBy:NSLayoutRelationEqual
                                           toItem:constrainer
                                        attribute:attribute
                                       multiplier:1.0
                                         constant:constant];
}

@end
