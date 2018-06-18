#import "NavRoutingRerouteDialog.h"

#include "CallbackCollection.h"

@interface NavRoutingRerouteDialog()
@property (retain, nonatomic) IBOutlet UILabel *messageLabel;
@end

@implementation NavRoutingRerouteDialog
{
    Eegeo::Helpers::CallbackCollection1<const bool> m_rerouteDialogClosedCallbacks;
}

@synthesize message = _message;

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
    UIView *pView = [[[NSBundle mainBundle] loadNibNamed:@"NavRoutingRerouteDialog" owner:self options:nil] objectAtIndex:0];
    pView.frame = frame;
    [self addSubview:pView];
}

- (void)dealloc
{
    [_messageLabel release];
    [super dealloc];
}

- (void) setMessage:(NSString *)message
{
    _message = message;
    _messageLabel.text = _message;
}

- (IBAction)updateRouteButtonTapped:(id)sender
{
    m_rerouteDialogClosedCallbacks.ExecuteCallbacks(true);
}

- (IBAction)endNavigationButtonTapped:(id)sender
{
    m_rerouteDialogClosedCallbacks.ExecuteCallbacks(false);
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    return YES;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    return YES;
}

- (void) InsertRerouteDialogClosedCallback:(Eegeo::Helpers::ICallback1<const bool>*) rerouteDialogClosedCallback
{
    m_rerouteDialogClosedCallbacks.AddCallback(*rerouteDialogClosedCallback);
}

- (void) RemoveRerouteDialogClosedCallback:(Eegeo::Helpers::ICallback1<const bool>*) rerouteDialogClosedCallback
{
    m_rerouteDialogClosedCallbacks.RemoveCallback(*rerouteDialogClosedCallback);
}

@end
