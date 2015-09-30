// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            bool SearchResultMenuOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
            {
                //GeoNames results on top
                if(a.GetVendor() != b.GetVendor() && a.GetVendor() == Search::GeoNamesVendorName)
                {
                        return true;
                }
                //Order GeoNames results as they came in
                if(a.GetVendor() == Search::GeoNamesVendorName || b.GetVendor() == Search::GeoNamesVendorName)
                {
                    return false;
                }
                return a < b;
            }
        }
    }
}