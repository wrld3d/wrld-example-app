// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ImageHelpers.h"

namespace
{
    NSString* GetImageScaleSuffix()
    {
        // This is not strictly neccessary for images loaded with [UIImage imageNamed:], but is done
        // so we have a consistent way to get the right texture name for non UIKit textures like the
        // 3D pins, GPS marker, POI marker, etc.
        
        int scale = 1;
        UIScreen* screen = [UIScreen mainScreen];
        if ([screen respondsToSelector: @selector(scale)])
        {
            scale = static_cast<int>(screen.scale);
        }
        
        if(scale == 2)
        {
            return @"@2x";
        }
        else if(scale == 3)
        {
            return @"@3x";
        }
        
        return @"";
    }
    
    NSString* GetImageNameForDevice(const NSString* name)
    {
        return [NSString stringWithFormat:@"%@%@", name, GetImageScaleSuffix()];
    }

    CGRect GetRect(UIView* pParentView,
                   UIView* pImageView,
                   ExampleApp::Helpers::ImageHelpers::OffsetValue offsetInParent)
    {
        const CGFloat imgClipWidth = pImageView.frame.size.width > pParentView.frame.size.width ? pParentView.frame.size.width : pImageView.frame.size.width;
        const CGFloat imgClipHeight = pImageView.frame.size.height > pParentView.frame.size.height ? pParentView.frame.size.height : pImageView.frame.size.height;
        const CGFloat ratioX = imgClipWidth / pImageView.frame.size.width;
        const CGFloat ratioY = imgClipHeight / pImageView.frame.size.height;
        const CGFloat imgWidth = imgClipWidth * (ratioX > ratioY ? ratioY : 1.f);
        const CGFloat imgHeight = imgClipHeight * (ratioY > ratioX ? ratioX : 1.f);

        CGRect frame = pParentView.frame;

        if((offsetInParent & ExampleApp::Helpers::ImageHelpers::Left) != 0)
        {
            frame.origin.x = 0.f;
        }
        else if((offsetInParent & ExampleApp::Helpers::ImageHelpers::Right) != 0)
        {
            frame.origin.x = (pParentView.frame.size.width) - (imgWidth);
        }
        else if((offsetInParent & ExampleApp::Helpers::ImageHelpers::LeftOf) != 0)
        {
            frame.origin.x = -(pImageView.frame.size.width);
        }
        else if((offsetInParent & ExampleApp::Helpers::ImageHelpers::RightOf) != 0)
        {
            frame.origin.x = (pParentView.frame.size.width);
        }
        else
        {
            frame.origin.x = (pParentView.frame.size.width / 2.f) - (imgWidth / 2.f);
        }

        if((offsetInParent & ExampleApp::Helpers::ImageHelpers::Top) != 0)
        {
            frame.origin.y = 0.f;
        }
        else if((offsetInParent & ExampleApp::Helpers::ImageHelpers::Bottom) != 0)
        {
            frame.origin.y = (pParentView.frame.size.height) - (imgHeight);
        }
        else if((offsetInParent & ExampleApp::Helpers::ImageHelpers::Above) != 0)
        {
            frame.origin.y = -(pImageView.frame.size.height);
        }
        else if((offsetInParent & ExampleApp::Helpers::ImageHelpers::Below) != 0)
        {
            frame.origin.y = (pParentView.frame.size.height);
        }
        else
        {
            frame.origin.y = (pParentView.frame.size.height / 2.f) - (imgHeight / 2.f);
        }

        return CGRectMake(frame.origin.x, frame.origin.y, imgWidth, imgHeight);
    }

    UIImageView* CreateImageView(UIView* pParentView,
                                 const std::string& fullName,
                                 const std::string* fullHighlightableName=NULL)
    {
        UIImage* pImage = ExampleApp::Helpers::ImageHelpers::LoadImage(fullName);
        
        UIImageView* pImageView;

        const bool useHighlight = fullHighlightableName != NULL;
        if(useHighlight)
        {
            UIImage* pHighlightImage = ExampleApp::Helpers::ImageHelpers::LoadImage(*fullHighlightableName);
            pImageView = [[UIImageView alloc] initWithImage:pImage highlightedImage:pHighlightImage];
            pImageView.userInteractionEnabled = true;

        }
        else
        {
            pImageView = [[UIImageView alloc] initWithImage:pImage];
        }

        pImageView.contentMode = UIViewContentModeScaleToFill;

        return pImageView;
    }

    UIImageView* AddImageToParentView(UIView* pParentView,
                                      const std::string& fullName,
                                      ExampleApp::Helpers::ImageHelpers::OffsetValue offsetInParent,
                                      const std::string* fullHighlightableName=NULL)
    {
        UIImageView* pImageView = CreateImageView(pParentView, fullName, fullHighlightableName);

        pImageView.frame = GetRect(pParentView, pImageView, offsetInParent);

        [pParentView addSubview:pImageView];

        return pImageView;
    }

    UIImageView* AddImageToParentView(UIView* pParentView,
                                      const std::string& fullName,
                                      float x, float y, float w, float h,
                                      const std::string* fullHighlightableName=NULL)
    {
        UIImageView* pImageView = CreateImageView(pParentView, fullName, fullHighlightableName);

        pImageView.frame = CGRectMake(x, y, w, h);

        [pParentView addSubview:pImageView];

        return pImageView;
    }
}

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ImageHelpers
        {
            UIImageView* AddPngImageToParentView(UIView* pParentView,
                                                 const std::string& name,
                                                 OffsetValue offsetInParent)
            {
                return AddImageToParentView(pParentView, name, offsetInParent, NULL);
            }

            UIImageView* AddPngImageToParentView(UIView* pParentView, const std::string& name, float x, float y, float w, float h)
            {
                return AddImageToParentView(pParentView, name, x, y, w, h, NULL);
            }

            UIImageView* AddPngHighlightedImageToParentView(UIView* pParentView,
                    const std::string& name,
                    const std::string& highlightedName,
                    OffsetValue offsetInParent)
            {
                return AddImageToParentView(pParentView, name, offsetInParent, &highlightedName);
            }
            
            std::string GetImageNameForDevice(const std::string& name,
                                              const std::string& ext)
            {
                NSString* nsStrName = [NSString stringWithUTF8String:name.c_str()];
                NSString* nsStrDeviceName = ::GetImageNameForDevice(nsStrName);
                std::string result = [nsStrDeviceName UTF8String];
                return result + ext;
            }
            
            UIImage* LoadImage(const std::string& name, bool permitFallbackToNonNativeResolution)
            {
                NSString* nsStrName = [NSString stringWithUTF8String:name.c_str()];
                return LoadImage(nsStrName, permitFallbackToNonNativeResolution);
            }
            
            UIImage* LoadImage(const NSString* name, bool permitFallbackToNonNativeResolution)
            {
                // Uncomment to validate image asset exists at native resolution; this is useful when debugging to detect
                // if iOS is silently falling back to an inappropriate image.
                const bool validateImageExists = false;
                
                if(validateImageExists && !permitFallbackToNonNativeResolution)
                {
                    UIImage* pImg = [UIImage imageNamed: ::GetImageNameForDevice(name)];
                    Eegeo_ASSERT(pImg != nil, "Missing image asset %s for current device resolution.\n", [name UTF8String]);
                }
                
                return [UIImage imageNamed: [NSString stringWithFormat:@"%@", name]];
            }
            
            UIImage* ImageFromColor(UIColor* color)
            {
                CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
                UIGraphicsBeginImageContext(rect.size);
                CGContextRef context = UIGraphicsGetCurrentContext();
                
                CGContextSetFillColorWithColor(context, [color CGColor]);
                CGContextFillRect(context, rect);
                
                UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
                UIGraphicsEndImageContext();
                
                return image;
            }
        }
    }
}
