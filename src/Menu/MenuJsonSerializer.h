// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
	namespace Menu
	{
		template <typename TMenuItem>
		std::string SerialiseMenuItemToJson(const TMenuItem& menuItem)
		{
			rapidjson::StringBuffer stringBuffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer = rapidjson::Writer<rapidjson::StringBuffer>(stringBuffer);

			writer.StartObject();

			if(!menuItem.Name().empty())
			{
				writer.String("name");
				writer.String(menuItem.Name().c_str(), menuItem.Name().size());
			}

			if(!menuItem.Details().empty())
			{
				writer.String("details");
				writer.String(menuItem.Details().c_str(), menuItem.Details().size());
			}

			if(!menuItem.Icon().empty())
			{
				writer.String("icon");
				writer.String(menuItem.Icon().c_str(), menuItem.Icon().size());
			}

			writer.EndObject();

			return std::string(stringBuffer.GetString(), stringBuffer.GetSize());
		}
	}
}
