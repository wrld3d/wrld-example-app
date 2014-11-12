// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <sstream>
#include <algorithm>
#include <vector>
#include "document.h"
#include "DecartaSearchJsonParser.h"
#include "LatLongAltitude.h"
#include "SearchResultModel.h"

using namespace rapidjson;

namespace
{
	struct Result
	{
		std::string placeId;
		std::string phone;
		std::string address;
		std::string webUrl;
		std::string name;
		std::string category;
		std::string vicinity;
		std::string uniqueId;
		Eegeo::Space::LatLong location;

		Result():location(0.f, 0.f) { }
	};
}

namespace ExampleApp
{
	namespace Search
	{
		namespace Decarta
		{
			void DecartaSearchJsonParser::ParseSearchResults(const std::string& serialized,
			        std::vector<SearchResultModel>& out_results)
			{
				Document document;

				if (!document.Parse<0>(serialized.c_str()).HasParseError())
				{
					if(document.HasMember("results"))
					{
						const Value& entries = document["results"];
						size_t numEntries = entries.Size();

						for(int i = 0; i < numEntries; ++i)
						{
							const Value& json = entries[i];
							Result entry;

							const Value& type = json["type"];
							std::string typeString = type.GetString();
							std::transform(typeString.begin(), typeString.end(), typeString.begin(), ::tolower);
							if(typeString != "poi" && typeString != "geography")
							{
								continue;
							}

							if(json.HasMember("position"))
							{
								const Value& position = json["position"];
								entry.location = Eegeo::Space::LatLong::FromDegrees(position["lat"].GetDouble(),
								                 position["lon"].GetDouble());


								entry.phone = "";
								entry.address = "";
								entry.webUrl = "";

								bool hasPoi = false;
								entry.name = "";

								if(json.HasMember("poi"))
								{
									hasPoi = true;
									const Value& name = json["poi"]["name"];
									entry.name = name.GetString();

									if(json["poi"].HasMember("categories"))
									{
										const Value& category = json["poi"]["categories"];
										entry.category = category[0u].GetString();

										if(json["poi"].HasMember("phone"))
										{
											entry.phone = json["poi"]["phone"].GetString();
										}

										if(json["poi"].HasMember("url"))
										{
											entry.webUrl = json["poi"]["url"].GetString();
										}
									}
								}

								if(json.HasMember("address"))
								{
									const Value& address = json["address"];

									if(address.HasMember("freeformAddress"))
									{
										const Value& vicinity = address["freeformAddress"];
										entry.vicinity = vicinity.GetString();
										entry.address = vicinity.GetString();

										if(!hasPoi)
										{
											entry.name = vicinity.GetString();
										}
									}
								}

								const Value& id = json["id"];
								std::stringstream ss;
								ss << id.GetUint64();
								entry.placeId = ss.str();

								// Decarta has duplicate ids in results, so need different unique ID for mapping.
								ss << "_" << i;
								entry.uniqueId = ss.str();

								SearchResultModel result(entry.uniqueId,
								                         entry.name,
								                         entry.location,
								                         entry.phone,
								                         entry.address,
								                         entry.webUrl,
								                         entry.category,
								                         entry.vicinity);

								out_results.push_back(result);
							}
						}
					}
				}
			}
		}
	}
}

