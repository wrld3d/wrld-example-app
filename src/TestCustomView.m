//
//  TestCustomView.m
//  ExampleApp
//

#import "TestCustomView.h"

@implementation TestCustomView

- (instancetype)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];
    if (self)
    {
        [self initNib];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self initNib];
    }
    return self;
}

- (UIView*)findView:(NSArray*)objects
{
    for (id object in objects)
    {
        if ([object isKindOfClass:[UIView class]])
        {
            return object;
        }
    }
    return nil;
}

- (void)initNib
{
    NSArray *objects = [[NSBundle mainBundle] loadNibNamed:@"TestCustomView" owner:self options:nil];
    UIView *containerView = [self findView:objects];

    containerView.translatesAutoresizingMaskIntoConstraints = NO;
    [self addSubview:containerView];
    [self setNeedsUpdateConstraints];
    
    NSDictionary *viewsDictionary = NSDictionaryOfVariableBindings(self, containerView);
    
    [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[containerView]-0-|" options:0 metrics: 0 views:viewsDictionary]];
    [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[containerView]-0-|" options:0 metrics: 0 views:viewsDictionary]];
}


@end