// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <limits>
#include <map>

#include "SearchResultSectionOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            namespace
            {
                int VendorPriority(const std::string& vendor)
                {
                    const int HighestPriority = std::numeric_limits<int>::max();
                    enum AscendingVendorPriority {
                        EegeoVendorPriority,
                        YelpVendorPriority,
                        GeoNamesVendorPriority
                    };

                    static const std::map<std::string, int> vendorPriorities{
                        {Search::EegeoVendorName,    EegeoVendorPriority},
                        {Search::YelpVendorName,     YelpVendorPriority},
                        {Search::GeoNamesVendorName, GeoNamesVendorPriority}};

                    const std::map<std::string, int>::const_iterator vendorIx = vendorPriorities.find(vendor);
                    return vendorIx != vendorPriorities.end()
                        ? vendorIx->second
                        : HighestPriority;
                }
            }

            bool SearchResultSectionOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
            {
                return VendorPriority(a.GetVendor()) < VendorPriority(b.GetVendor());
            }
        }
    }
}