// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"


namespace ExampleApp
{
    namespace PoiDb
    {
        class IPoiDbModule
        {
        public:
            virtual ~IPoiDbModule() {;}
            
            virtual IPoiDbWebLoader& GetPoiDbWebLoader() const = 0;
            
            virtual bool IsPoiDbServiceStarted() const = 0;
            
            virtual bool TryGetPoiDbService(IPoiDbService*& out_pService) const = 0;
        };
    }
}