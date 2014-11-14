// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ImageHelpers.h"

namespace
{
	std::string GetImageNameForDevice(const std::string& name)
	{
		// todo: either return name of normal or high res image for retina or non retina
		return name;
	}

	CGRect GetRect(UIView* pParentView,
	               UIView* pImageView,
	               ExampleApp::Helpers::ImageHelpers::OffsetValue offsetInParent)
	{
		const float imgClipWidth = pImageView.frame.size.width > pParentView.frame.size.width ? pParentView.frame.size.width : pImageView.frame.size.width;
		const float imgClipHeight = pImageView.frame.size.height > pParentView.frame.size.height ? pParentView.frame.size.height : pImageView.frame.size.height;
		const float ratioX = imgClipWidth / pImageView.frame.size.width;
		const float ratioY = imgClipHeight / pImageView.frame.size.height;
		const float imgWidth = imgClipWidth * (ratioX > ratioY ? ratioY : 1.f);
		const float imgHeight = imgClipHeight * (ratioY > ratioX ? ratioX : 1.f);

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
		NSString* pNameString = [NSString stringWithUTF8String:fullName.c_str()];

		UIImage* pImage = [UIImage imageNamed:pNameString];

		UIImageView* pImageView;

		const bool useHighlight = fullHighlightableName != NULL;
		if(useHighlight)
		{
			NSString* pHighlightNameString = [NSString stringWithUTF8String:fullHighlightableName->c_str()];
			UIImage* pHighlightImage = [UIImage imageNamed:pHighlightNameString];
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

	void AddImageToParentView(UIView* pParentView,
	                          const std::string& fullName,
	                          ExampleApp::Helpers::ImageHelpers::OffsetValue offsetInParent,
	                          CGRect& out_imageFrame,
	                          const std::string* fullHighlightableName=NULL)
	{
		UIImageView* pImageView = CreateImageView(pParentView, fullName, fullHighlightableName);

		pImageView.frame = GetRect(pParentView, pImageView, offsetInParent);

		[pParentView addSubview:pImageView];

		out_imageFrame = pImageView.frame;
	}

	void AddImageToParentView(UIView* pParentView,
	                          const std::string& fullName,
	                          float x, float y, float w, float h,
	                          CGRect& out_imageFrame,
	                          const std::string* fullHighlightableName=NULL)
	{
		UIImageView* pImageView = CreateImageView(pParentView, fullName, fullHighlightableName);

		pImageView.frame = CGRectMake(x, y, w, h);

		[pParentView addSubview:pImageView];

		out_imageFrame = pImageView.frame;
	}
}

namespace ExampleApp
{
	namespace Helpers
	{
		namespace ImageHelpers
		{
			CGRect AddPngImageToParentView(UIView* pParentView,
			                               const std::string& name,
			                               OffsetValue offsetInParent)
			{
				std::string fullName = GetImageNameForDevice(name) + ".png";
				CGRect imageFrame;
				AddImageToParentView(pParentView, fullName, offsetInParent, imageFrame, NULL);
				return imageFrame;
			}

			CGRect AddPngImageToParentView(UIView* pParentView, const std::string& name, float x, float y, float w, float h)
			{
				std::string fullName = GetImageNameForDevice(name) + ".png";
				CGRect imageFrame;
				AddImageToParentView(pParentView, fullName, x, y, w, h, imageFrame, NULL);
				return imageFrame;
			}

			CGRect AddPngHighlightedImageToParentView(UIView* pParentView,
			        const std::string& name,
			        const std::string& highlightedName,
			        OffsetValue offsetInParent)
			{
				std::string fullName = GetImageNameForDevice(name) + ".png";
				std::string fullHighlightedName = GetImageNameForDevice(highlightedName) + ".png";
				CGRect imageFrame;
				AddImageToParentView(pParentView, fullName, offsetInParent, imageFrame, &fullHighlightedName);
				return imageFrame;
			}
		}
	}
}
