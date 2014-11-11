// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "writer.h"
#include "stringbuffer.h"
#include "document.h"
#include "AndroidSearchResultSerializer.h"
#include "Types.h"
#include "LatLongAltitude.h"
#include "Logger.h"

namespace
{
	void WriteProperty(
			const std::string& value,
			const std::string& identifier,
			rapidjson::Writer<rapidjson::StringBuffer>& writer)
	{
		writer.String(identifier.c_str());
		writer.String(value.c_str(), value.size());
	}

	void WriteProperty(
            const Eegeo::Space::LatLong& location,
			const std::string& identifier,
			rapidjson::Writer<rapidjson::StringBuffer>& writer)
	{
		writer.String(identifier.c_str());
		writer.StartArray();
		writer.Double(location.GetLatitude());
		writer.Double(location.GetLongitude());
		writer.EndArray(2);
	}

	void SerializeSearchResult(
			const ExampleApp::Search::SearchResultModel& searchResult,
			rapidjson::Writer<rapidjson::StringBuffer>& writer)
	{
        writer.StartObject();

        WriteProperty(searchResult.GetIdentifier(), "identifier", writer);
        WriteProperty(searchResult.GetTitle(), "title", writer);
        WriteProperty(searchResult.GetLocation(), "location", writer);
        WriteProperty(searchResult.GetPhone(), "phone", writer);
        WriteProperty(searchResult.GetAddress(), "address", writer);
        WriteProperty(searchResult.GetWebUrl(), "url", writer);
        WriteProperty(searchResult.GetCategory(), "category", writer);
        WriteProperty(searchResult.GetVicinity(), "vicinity", writer);

        writer.EndObject();
	}

	ExampleApp::Search::SearchResultModel DeserializeSearchResult(const rapidjson::Value& json)
	{
		Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromRadians(
			json["location"][0u].GetDouble(),
			json["location"][1u].GetDouble()
		);

		return ExampleApp::Search::SearchResultModel(
			json["identifier"].GetString(),
			json["title"].GetString(),
			location,
			json["phone"].GetString(),
			json["address"].GetString(),
			json["url"].GetString(),
			json["category"].GetString(),
			json["vicinity"].GetString()
		);
	}
}

namespace ExampleApp
{
    namespace AndroidSearchResultSerializer
    {
    	std::string SerializeSearchResult(const Search::SearchResultModel& searchResult)
    	{
            rapidjson::StringBuffer stringBuffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer = rapidjson::Writer<rapidjson::StringBuffer>(stringBuffer);

            ::SerializeSearchResult(searchResult, writer);

            return std::string(stringBuffer.GetString(), stringBuffer.GetSize());
    	}

    	Search::SearchResultModel DeserializeSearchResult(const std::string& searchResult)
    	{
    		rapidjson::Document document;
    		document.Parse<0>(searchResult.c_str());

			Eegeo_ASSERT(!document.HasParseError(), "Unable to parse serialized search result.\n");

			return ::DeserializeSearchResult(document);
    	}
    }
}
