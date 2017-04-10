// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            template <typename TMenuItem>
            std::string SerialiseMenuItemToJson(const TMenuItem& menuItem)
            {
                rapidjson::StringBuffer stringBuffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);

                writer.StartObject();

                writer.String("name");
                writer.String(menuItem.Name().c_str(), static_cast<rapidjson::SizeType>(menuItem.Name().size()));

                if(!menuItem.Details().empty())
                {
                    writer.String("details");
                    writer.String(menuItem.Details().c_str(), static_cast<rapidjson::SizeType>(menuItem.Details().size()));
                }

                writer.String("icon");
                writer.String(menuItem.Icon().c_str(), static_cast<rapidjson::SizeType>(menuItem.Icon().size()));

                writer.EndObject();

                return std::string(stringBuffer.GetString(), stringBuffer.GetSize());
            }
        }
    }
}
