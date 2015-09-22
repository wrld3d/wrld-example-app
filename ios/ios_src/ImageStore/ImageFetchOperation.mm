// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import <UIKit/UIKit.h>
#import "ImageFetchOperation.h"

@implementation ImageFetchOperation
{
    NSURL* m_imageUrl;
    float m_cropSize;
}

- (id)initWithUrl:(NSURL*)url
{
    return [self initWithParams:url :0.0f];
}

- (id)initWithParams:(NSURL*)url :(float)cropSize
{
    if(self = [super init])
    {
        m_imageUrl = [url copy];
        m_cropSize = cropSize;
    }
    
    return self;
}

- (void) dealloc
{
    [m_imageUrl release];
    
    [super dealloc];
}

- (void)main
{
    // start the image load
    NSData* imageData = [NSData dataWithContentsOfURL:m_imageUrl];
    
    UIImage* image = [UIImage imageWithData:imageData];
    
    // crop the image if necessary
    if(m_cropSize >= 1.0f)
    {
        if(image.size.width > m_cropSize || image.size.height > m_cropSize)
        {
            float xScale = m_cropSize / image.size.width;
            float yScale = m_cropSize / image.size.height;
            
            float scaleFactor = xScale > yScale ? yScale : xScale;
            
            CGSize newSize = CGSizeMake(image.size.width * scaleFactor, image.size.height * scaleFactor);
            
            UIGraphicsBeginImageContextWithOptions(newSize, YES, 0.0);
            [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
            image = UIGraphicsGetImageFromCurrentImageContext();
            UIGraphicsEndImageContext();
        }
    }
    
    // call the delegate, pass control of the image
    if(self.delegate != nil)
    {
        [self.delegate onImageFetchComplete:m_imageUrl :image];
    }
}

@end