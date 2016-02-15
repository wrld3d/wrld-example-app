// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class IEegeoSearchQuery
                {
                public:
                    virtual ~IEegeoSearchQuery() { }
                    
                    virtual void Cancel() = 0;
                    
                    virtual bool IsSucceeded() = 0;
                    
                    virtual const std::string& ResponseString() = 0;
                };
            }
        }
    }
}
