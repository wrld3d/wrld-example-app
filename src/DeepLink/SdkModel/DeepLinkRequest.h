// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "AppInterface.h"
#include <string>

namespace ExampleApp
{
	namespace DeepLink
	{
		namespace SdkModel
		{
			class DeepLinkRequest
			{
				std::string m_host;
				std::string m_path;
				std::string m_query;

			public:
				DeepLinkRequest(const AppInterface::UrlData& data)
				: m_host (data.host  == NULL ? "" : data.host)
				, m_path (data.path  == NULL ? "" : data.path)
				, m_query(data.query == NULL ? "" : data.query)
				{
				}

				const std::string& Host () const	{ return m_host;  }
				const std::string& Path () const	{ return m_path;  }
				const std::string& Query() const	{ return m_query; }
			};
		}
	}
}
