#import "NavRoutingCalculatingRoute.h"

@interface NavRoutingCalculatingRoute()
@property (retain, nonatomic) IBOutlet UIImageView *spinners;

@end

const float SpinnerPeriod = 2.0f;

@implementation NavRoutingCalculatingRoute
{
    BOOL isAnimating;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    if((self = [super initWithFrame:frame]))
    {
        [self initCommon: frame];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    if((self = [super initWithCoder:aDecoder]))
    {
        [self initCommon: self.bounds];
    }
    return self;
}

- (void)initCommon:(CGRect)frame
{
    UIView *pView = [[[NSBundle mainBundle] loadNibNamed:@"NavRoutingCalculatingRoute" owner:self options:nil] objectAtIndex:0];
    pView.frame = frame;
    [self addSubview:pView];
    
}

- (void)dealloc
{
    [_spinners release];
    [super dealloc];
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    return YES;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    return YES;
}

- (void) setSpinnerState:(bool) state
{
    if(state)
    {
        isAnimating = YES;
        [self animate];
    }
    else
    {
        isAnimating = NO;
    }
}

- (void)animate
{
    // adds a 90 degree rotation
    [UIView animateWithDuration: SpinnerPeriod / 4.0f
                          delay: 0.0f
                        options: UIViewAnimationOptionCurveLinear
                     animations: ^{
                         _spinners.transform = CGAffineTransformRotate(_spinners.transform, static_cast<float>(M_PI / SpinnerPeriod));
                     }
                     completion: ^(BOOL finished){
                         if (finished)
                         {
                             if (isAnimating)
                             {
                                 [self animate];
                             }
                         }
                     }];
}

@end
