// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IAboutPageModel.h"

namespace ExampleApp
{
	namespace AboutPage
	{
		class AboutPageModel : public IAboutPageModel, private Eegeo::NonCopyable
		{
			std::string m_platformVersion;
			std::string m_platformHash;
			std::string m_aboutText;

		public:
			AboutPageModel(const std::string& platformVersion,
			               const std::string& platformHash,
			               const std::string& aboutText);

			~AboutPageModel();

			const std::string& GetPlatformVersion() const;

			const std::string& GetPlatformHash() const;

			const std::string& GetAboutText() const;
		};
	}
}
