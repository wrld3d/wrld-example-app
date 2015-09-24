// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class IGeoNamesSearchQuery
                {
                public:
                    virtual ~IGeoNamesSearchQuery() { }
                    
                    virtual void Cancel() = 0;
                    
                    virtual bool IsSucceeded() = 0;
                    
                    virtual const std::string& ResponseString() = 0;
                };
            }
        }
    }
}
