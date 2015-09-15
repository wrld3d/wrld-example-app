// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourHovercardView.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "TourHovercardViewInterop.h"
#include "App.h"
#include "Document.h"
#include "ImageStore.h"
#include "TourDefines.h"

@implementation TourHovercardView
{
    ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_stateChangeAnimationTimeSeconds;
    float m_pinOffset;
    float m_pixelScale;
    
    float m_width;
    float m_height;
    float m_labelHeight;
    float m_arrowSize;
    float m_cornerRadius;
    
    float m_x;
    float m_y;
    
    std::string m_labelContent;
    std::string m_imagePath;
    std::string m_contentUrl;
    bool m_isVideo;
    
    CAShapeLayer* m_maskLayer;
    CAShapeLayer* m_shadowLayer;
    CAShapeLayer* m_shapeLayer;
    
    ExampleApp::Helpers::ColorHelpers::Color m_baseColor;
    ExampleApp::Helpers::ColorHelpers::Color m_textColor;
    
    ImageStore* m_pImageStore;
}

- (id)initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore
{
    self = [super init];
    
    if(self)
    {
        m_pImageStore = pImageStore;
        
        m_width = 250.0f;
        m_height = 150.0f;
        m_labelHeight = 30.f;
        m_arrowSize = 25.f;
        m_cornerRadius = 15.f;
        
        self.alpha = 0.f;
        self.layer.shouldRasterize = YES;
        self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
        
        m_pinOffset = (pinDiameter * pixelScale);
        m_pixelScale = pixelScale;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapped:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer: m_tapGestureRecogniser];
        
        m_pInterop = new ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop(self);
        
        self.pMainControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, m_width, m_height)] autorelease];
        self.pBackgroundImage = [[[FXImageView alloc] initWithFrame:CGRectMake(0, 0, m_width, m_height)] autorelease];
        self.pBackgroundImage.asynchronous = YES;
        self.pBackgroundSubImage = [[[FXImageView alloc] initWithFrame:CGRectMake(0, 0, m_width, m_height)] autorelease];
        self.pBackgroundSubImage.contentMode = UIViewContentModeScaleAspectFill;
        self.pBackgroundSubImage.asynchronous = NO;
        self.pMainShape = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_width, m_height)] autorelease];
        self.pNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, m_width, 0)] autorelease];
        self.pNameLabelBackground = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_width, m_height)] autorelease];
        
        [self addSubview: self.pMainControlContainer];

        m_pPlayIconImage = ExampleApp::Helpers::ImageHelpers::LoadImage("Tours/play_icon");

        m_maskLayer = nil;
        m_shadowLayer = nil;
        m_shapeLayer = nil;
        
        m_x = 0.0f;
        m_y = 0.0f;
    }

    return self;
}


- (void) setPresentationColors :(ExampleApp::Helpers::ColorHelpers::Color)baseColor :(ExampleApp::Helpers::ColorHelpers::Color)textColor
{
    m_baseColor = baseColor;
    m_textColor = textColor;
}

- (void)dealloc
{
    [m_pPlayIconImage release];
    m_pPlayIconImage = nil;
    
    if(m_maskLayer != nil)
    {
        [m_maskLayer removeFromSuperlayer];
        [m_shadowLayer removeFromSuperlayer];
        [m_shadowLayer removeFromSuperlayer];
    }
    
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];
    
    [self.pNameLabelBackground removeFromSuperview];
    [self.pNameLabelBackground release];
    
    [self.pBackgroundSubImage removeFromSuperview];
    [self.pBackgroundSubImage release];
    self.pBackgroundSubImage = nil;
    
    [m_pImageStore releaseImageForView:self.pBackgroundImage];
    
    [self.pBackgroundImage removeFromSuperview];
    [self.pBackgroundImage release];
    
    [self.pMainShape removeFromSuperview];
    [self.pMainShape release];
    
    [self.pMainControlContainer removeFromSuperview];
    [self.pMainControlContainer release];
    
    delete m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

-(void) clear
{
    if(self.pBackgroundImage.processedImage != nil)
    {
        [self.pBackgroundImage setImage:nil];
    }
    
    self.pMainControlContainer.backgroundColor = [UIColor clearColor];
    
    self.pMainControlContainer.layer.shadowRadius = 0.0f;
    self.pMainControlContainer.layer.shadowOpacity = 0.0f;
    self.pMainControlContainer.layer.borderWidth = 0.0f;
    
    if(m_maskLayer != nil)
    {
        [m_maskLayer removeFromSuperlayer];
        m_maskLayer = nil;
    }
    
    if(m_shadowLayer != nil)
    {
        m_shadowLayer = nil;
    }
    
    if(m_shapeLayer != nil)
    {
        [m_shapeLayer removeFromSuperlayer];
        m_shapeLayer = nil;
    }
    
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabelBackground removeFromSuperview];
    [self.pBackgroundSubImage removeFromSuperview];
    [self.pBackgroundImage removeFromSuperview];
    [self.pMainShape removeFromSuperview];
    
    self.pBackgroundImage.layer.borderWidth = 0.0f;
    
    for (CALayer *layer in [[self.pNameLabelBackground.layer.sublayers copy] autorelease]) {
        [layer removeFromSuperlayer];
    }
    
    for (CALayer *layer in [[self.pNameLabel.layer.sublayers copy] autorelease]) {
        [layer removeFromSuperlayer];
    }
    
    for (CALayer *layer in [[self.pMainShape.layer.sublayers copy] autorelease]) {
        [layer removeFromSuperlayer];
    }
}

-(void)layoutSubviews
{
    [super layoutSubviews];

    const bool isPhone = App::IsDeviceSmall();
    
    m_arrowSize = isPhone ? 20.0f : 30.0f;
    
    m_width = isPhone ? 120.0f : 180.0f;
    m_height = isPhone ? 120.0f +  m_arrowSize : 180.0f + m_arrowSize;
    m_labelHeight = isPhone ? 30.0f : 50.f;
    
    m_cornerRadius = 0.f;
    
    const float backgroundSubImageSize = isPhone ? 48.0f : 64.0f;
    
    [self setNameLabelContent:m_labelContent :m_labelHeight];
    [self clear];
    
    const float labelHeight = self.pNameLabel.bounds.size.height;
    const float borderWidth = isPhone ? 2.0f : 3.0f;
    
    const bool hasImage = !m_imagePath.empty();
    if(hasImage)
    {
        [m_pImageStore releaseImageForView:self.pBackgroundImage];
        
        if(m_imagePath.find("http") != std::string::npos)
        {
            [m_pImageStore loadImage:m_imagePath
                                    :self.pBackgroundImage
                                    :^(UIImage* image)
                                     {
                                         self.pBackgroundImage.image = image;
                                     }
                                    :TourDefines::ProfileImageSize];
        }
        else
        {
            UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(m_imagePath);
            [self.pBackgroundImage setImage:image];
        }
    }
    else
    {
        m_height = m_labelHeight + m_arrowSize + 2 * borderWidth;
        [self.pBackgroundImage setImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor([UIColor whiteColor])];
    }
    
    const float fullControlHeight = hasImage ? m_height : m_labelHeight + m_arrowSize + 2 * borderWidth;
    const float mainControlHeight = fullControlHeight - m_arrowSize;
    
    self.frame = CGRectMake(self.frame.origin.x,
                            self.frame.origin.y,
                            m_width,
                            fullControlHeight);
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, m_width, fullControlHeight);
    self.pMainControlContainer.backgroundColor = [UIColor clearColor];
    
    self.pMainShape.frame = CGRectMake(0, 0, m_width, m_height);
    m_shapeLayer = [self createBubbleLayer:m_width :m_height :m_arrowSize :m_cornerRadius];
    [m_shapeLayer setFillColor:[UIColor whiteColor].CGColor];
    [m_shapeLayer setLineWidth:borderWidth];
    [m_shapeLayer setStrokeColor:[UIColor whiteColor].CGColor];
    self.pMainShape.backgroundColor = [UIColor clearColor];
    [self.pMainShape.layer addSublayer:m_shapeLayer];
    
    [self.pMainControlContainer addSubview:self.pMainShape];
    
    self.pMainControlContainer.layer.shadowColor = [UIColor blackColor].CGColor;
    self.pMainControlContainer.layer.shadowRadius = 10.0f;
    self.pMainControlContainer.layer.shadowOpacity = 0.8f;
    self.pMainControlContainer.layer.shadowOffset = CGSizeMake(0.0f, 8.0f);
    m_shadowLayer = [self createBubbleLayer:m_width :m_height :m_arrowSize :m_cornerRadius];
    self.pMainControlContainer.layer.shadowPath = m_shadowLayer.path;
    
    
    
    self.pBackgroundSubImage.hidden = !m_isVideo;
    
    [self.pBackgroundSubImage setImage:m_pPlayIconImage];
    self.pBackgroundSubImage.frame = CGRectMake((m_width - backgroundSubImageSize) / 2.0f, (mainControlHeight - backgroundSubImageSize) / 2.0f, backgroundSubImageSize, backgroundSubImageSize);
    
    [self.pBackgroundImage addSubview:self.pBackgroundSubImage];
    
    self.pBackgroundImage.contentMode = UIViewContentModeScaleAspectFill;
    self.pBackgroundImage.clipsToBounds = YES;
    self.pBackgroundImage.frame = CGRectMake(0, 0, m_width, mainControlHeight);
    
    [self.pMainControlContainer addSubview: self.pBackgroundImage];
    
    const float textSize = isPhone ? 12.0f : 15.0f;
    self.pNameLabel.textColor = [UIColor whiteColor];
    self.pNameLabel.textAlignment = NSTextAlignmentCenter;
    self.pNameLabel.font = [UIFont fontWithName:@"GothamNarrow-Book" size:textSize];
    self.pNameLabel.backgroundColor = [UIColor clearColor];
    
    self.pNameLabelBackground.frame = CGRectMake(0, mainControlHeight - (m_labelHeight), m_width, m_labelHeight);
    self.pNameLabel.frame = CGRectMake(0, m_labelHeight*0.5f - labelHeight * 0.5f, self.pNameLabelBackground.frame.size.width, labelHeight);
    self.pNameLabelBackground.backgroundColor = [UIColor clearColor];
    
    CAGradientLayer *gradient = [CAGradientLayer layer];
    gradient.frame =  CGRectMake(0.f, 0.f, self.pNameLabelBackground.bounds.size.width, self.pNameLabelBackground.bounds.size.height);
    
    UIColor *topColor = [UIColor clearColor];
    UIColor *bottomColor = [UIColor blackColor];
    gradient.colors = [NSArray arrayWithObjects:(id)[topColor CGColor], (id)[bottomColor CGColor], nil];
    
    [self.pNameLabelBackground.layer insertSublayer:gradient atIndex:0];
    [self.pNameLabelBackground addSubview:self.pNameLabel];
    
    [self.pMainControlContainer addSubview:self.pNameLabelBackground];
    
    [self updatePosition:m_x :m_y];

}

-(void)setNameLabelContent:(const std::string&)content :(float)mainContainerHeight
{
    self.pNameLabel.numberOfLines = 0;
    self.pNameLabel.text = [NSString stringWithUTF8String:content.c_str()];
    
    float nameLabelWidth = self.pNameLabelBackground.frame.size.width;
    [self.pNameLabel sizeToFit];
    
    self.pNameLabelBackground.frame = CGRectMake(0,
                                                 mainContainerHeight - self.pNameLabel.frame.size.height,
                                                 nameLabelWidth,
                                                 self.pNameLabel.frame.size.height);
    
    float xPadding = 4.f;
    
    self.pNameLabel.frame = CGRectMake(xPadding,
                                       0,
                                       nameLabelWidth - (2.f * xPadding),
                                       self.pNameLabel.frame.size.height);
}

- (CAShapeLayer*) createBubbleLayer:(float)width :(float)height :(float)arrowSize :(float)cornerRadius
{
    float mainContainerHeight = height - arrowSize;
    CAShapeLayer *pathLayer = [CAShapeLayer layer];
    [pathLayer setBounds:CGRectMake(0.0f, 0.0f, self.pMainShape.bounds.size.width, self.pMainShape.bounds.size.height)];
    [pathLayer setPosition:self.pMainControlContainer.center];
    UIBezierPath *path = [UIBezierPath bezierPath];
    [path moveToPoint:CGPointMake(cornerRadius, 0)];
    [path addLineToPoint:CGPointMake(width-cornerRadius, 0)];
    [path addQuadCurveToPoint:CGPointMake(width, cornerRadius) controlPoint:CGPointMake(width, 0)];
    [path addLineToPoint:CGPointMake(width, mainContainerHeight - cornerRadius)];
    [path addQuadCurveToPoint:CGPointMake(width-cornerRadius, mainContainerHeight) controlPoint:CGPointMake(width, mainContainerHeight)];
    
    // Arrow
    [path addLineToPoint:CGPointMake(width*0.5f + arrowSize*0.5f, mainContainerHeight)];
    [path addLineToPoint:CGPointMake(width*0.5f, height)];
    [path addLineToPoint:CGPointMake(width*0.5f - arrowSize*0.5f, mainContainerHeight)];
    
    [path addLineToPoint:CGPointMake(cornerRadius, mainContainerHeight)];
    [path addQuadCurveToPoint:CGPointMake(0, mainContainerHeight-cornerRadius) controlPoint:CGPointMake(0, mainContainerHeight)];
    [path addLineToPoint:CGPointMake(0, cornerRadius)];
    [path addQuadCurveToPoint:CGPointMake(cornerRadius, 0) controlPoint:CGPointMake(0, 0)];
    [path closePath];
    
    [pathLayer setPath:[path CGPath]];
    [pathLayer setStrokeColor:[[UIColor colorWithRed:m_baseColor.GetRedF() green:m_baseColor.GetGreenF() blue:m_baseColor.GetBlueF() alpha:1.0f] CGColor]];
    [pathLayer setFillColor:[[UIColor clearColor] CGColor]];
    [pathLayer setLineWidth:3.0f];

    return pathLayer;
}

- (ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) setContent:(const std::string&)name :(const std::string&)data;
{
    m_isVideo = false;
    
    m_labelContent = name;
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(data.c_str());
    
    if(jsonDocument.HasParseError())
    {
        m_imagePath = data;
    }
    else
    {
        Eegeo_ASSERT(jsonDocument.HasMember("pinImageUrl") &&
                     jsonDocument.HasMember("pinContentUrl") &&
                     jsonDocument.HasMember("isVideo"));
        
        m_imagePath = jsonDocument["pinImageUrl"].GetString();
        m_contentUrl = jsonDocument["pinContentUrl"].GetString();
        m_isVideo = jsonDocument["isVideo"].GetBool();
    }
    
    [self setNeedsLayout];
}

- (void) setFullyActive :(float)modality
{
    self.userInteractionEnabled = YES;
    [self animateToAlpha:(1.f - modality)];
}

- (void) setFullyInactive
{
    self.userInteractionEnabled = NO;
    [self animateToAlpha:0.f];
}

- (void) updatePosition:(float)x :(float)y
{
    CGRect f = self.frame;
    f.origin.x = (x/m_pixelScale) - (f.size.width/2.f);
    f.origin.y = (y/m_pixelScale) - (f.size.height) - (m_pinOffset/m_pixelScale);
    self.frame = f;
    m_x = x;
    m_y = y;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(self.userInteractionEnabled)
    {
        CGPoint touchLocation = [touch locationInView:self];
        return CGRectContainsPoint(self.bounds, touchLocation);
    }
    
    return false;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.alpha = alpha;
     }];
}

- (void) onTapped:(UITapGestureRecognizer *)recognizer
{
    m_pInterop->OnSelected();
}

@end
