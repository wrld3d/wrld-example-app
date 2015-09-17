// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "Types.h"
#include "PoiDbWebLoader.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        class PoiDbServiceProvider : public Eegeo::Helpers::TCallback1<PoiDbServiceProvider, IPoiDbService*>, Eegeo::NonCopyable
        {
        public:
            PoiDbServiceProvider();
            
            ~PoiDbServiceProvider();
        
            bool TryGetService(IPoiDbService*& out_pService) const;
            
            bool IsPoiDbServiceStarted() const { return m_pPoiDbService != NULL; }
            
            void PoiDbWebLoaderCompleted(PoiDb::IPoiDbService*& pPoiDbService);
        private:
            IPoiDbService* m_pPoiDbService;
        };
    }
}