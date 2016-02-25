// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchResultMenuOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            namespace Swallow
            {   
                bool SwallowSearchResultMenuOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                {
                    //eeGeo results on top
                    if(a.GetVendor() != b.GetVendor() && a.GetVendor() == Search::EegeoVendorName)
                    {
                            return true;
                    }
                    //Order eeGeo results as they came in
                    if(a.GetVendor() == Search::EegeoVendorName || b.GetVendor() == Search::EegeoVendorName)
                    {
                        return false;
                    }
                    return a < b;
                }
            }
        }
    }
}