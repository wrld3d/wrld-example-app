// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiDbServiceProvider.h"
#include "PoiDbService.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        PoiDbServiceProvider::PoiDbServiceProvider()
        : m_pPoiDbService(NULL)
        , Eegeo::Helpers::TCallback1<PoiDbServiceProvider, IPoiDbService*>(this, &PoiDbServiceProvider::PoiDbWebLoaderCompleted)
        {
            
        }
        
        PoiDbServiceProvider::~PoiDbServiceProvider()
        {
            Eegeo_DELETE m_pPoiDbService;
        }
    
        
        void PoiDbServiceProvider::PoiDbWebLoaderCompleted(PoiDb::IPoiDbService*& pPoiDbService)
        {
            Eegeo_DELETE m_pPoiDbService;
            m_pPoiDbService = pPoiDbService;
        }
        
        bool PoiDbServiceProvider::TryGetService(IPoiDbService*& out_pService) const
        {
            out_pService = m_pPoiDbService;
            return (m_pPoiDbService != NULL);
        }
     }
}
