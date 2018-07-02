#import <Foundation/Foundation.h>

#import "NavSearchContainerView.h"
#import <WrldSearchWidget/WrldSearchWidget.h>

@interface NavSearchContainerView()
- (BOOL) consumesTouch:(UITouch *)touch;
- (void) setVisible:(BOOL) isVisible;
@end

@implementation NavSearchContainerView
{
    WRLDSearchWidgetView* m_searchView;
    UIView* m_backButton;
}

- (instancetype) initWithSubviews: (WRLDSearchWidgetView*) searchView :(UIView*) backButton
{
    CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ?
    CGRectMake(20, -50, 375, 300) :   // ipad
    CGRectMake(10, -50, CGRectGetWidth([[UIScreen mainScreen] bounds]) - 20, 300); // iphone
    
    if(self == [super initWithFrame:searchFrame])
    {
        m_searchView = searchView;
        m_backButton = backButton;
        
        [self addSubview: m_searchView];
        [self addSubview: m_backButton];
        [self setHidden:YES];
        [self constrainSubviews];
    }
    return self;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    BOOL consume =  [m_searchView pointInside:[touch locationInView:m_searchView] withEvent:nil] ||
                    [m_backButton pointInside:[touch locationInView:m_backButton] withEvent:nil];
    return consume;
}

- (void) setVisible:(BOOL) isVisible
{
    [self setHidden: !isVisible];
}

-(void) constrainSubviews
{
    m_searchView.translatesAutoresizingMaskIntoConstraints = false;
    m_backButton.translatesAutoresizingMaskIntoConstraints = false;
    
    NSLayoutConstraint* searchTop = [self constrainAttribute: NSLayoutAttributeTop of: m_searchView to: self withOffset: 0];
    NSLayoutConstraint* searchBottom = [self constrainAttribute: NSLayoutAttributeBottom of: m_searchView to: self withOffset: 0];
    NSLayoutConstraint* searchLeading = [self constrainAttribute: NSLayoutAttributeLeading of: m_searchView to: self withOffset: 40];
    NSLayoutConstraint* searchTrailing = [self constrainAttribute: NSLayoutAttributeTrailing of: m_searchView to: self withOffset: 0];
    
    NSLayoutConstraint* backTop = [self constrainAttribute: NSLayoutAttributeTop of: m_backButton to: m_searchView withOffset: 0];
    NSLayoutConstraint* backHeight = [NSLayoutConstraint constraintWithItem:m_backButton
                                                                  attribute:NSLayoutAttributeBottom
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:m_searchView.suggestionsContainer
                                                                  attribute:NSLayoutAttributeTop
                                                                 multiplier:1.0
                                                                   constant:0];
    
    NSLayoutConstraint* backLeading = [self constrainAttribute: NSLayoutAttributeLeading of: m_backButton to: self withOffset: 0];
    NSLayoutConstraint* backTrailing = [NSLayoutConstraint constraintWithItem:m_backButton
                                                                    attribute:NSLayoutAttributeTrailing
                                                                    relatedBy:NSLayoutRelationEqual
                                                                       toItem:m_searchView
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
