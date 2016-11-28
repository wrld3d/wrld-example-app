// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbServiceProvider.h"

#include "SwallowPoiDbCombinedService.h"
#include "WorldPinsService.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        SwallowPoiDbServiceProvider::SwallowPoiDbServiceProvider()
        : m_pSwallowPoiDbService(NULL)
        , Eegeo::Helpers::TCallback1<SwallowPoiDbServiceProvider, SwallowPoiDbCombinedService*>(this, &SwallowPoiDbServiceProvider::SwallowPoiDbWebLoaderCompleted)
        {
            
        }
        
        SwallowPoiDbServiceProvider::~SwallowPoiDbServiceProvider()
        {
            Eegeo_DELETE m_pSwallowPoiDbService;
        }
        
        void SwallowPoiDbServiceProvider::SwallowPoiDbWebLoaderCompleted(SwallowPoiDbCombinedService*& pSwallowPoiDbService)
        {
            Eegeo_DELETE m_pSwallowPoiDbService;
            m_pSwallowPoiDbService = pSwallowPoiDbService;
            
            std::vector<Search::SdkModel::SearchResultModel> transitionResults;
            
            if(pSwallowPoiDbService != NULL)
            {
                pSwallowPoiDbService->GetTransitionResults(transitionResults);
                m_transitionsLoadedCallbacks.ExecuteCallbacks(transitionResults);
            }
            else
            {
                Eegeo_TTY("Transition result fetch failed - No DB");
            }
        }
        
        bool SwallowPoiDbServiceProvider::TryGetSwallowPoiDbService(SwallowPoiDbCombinedService*& out_pService) const
        {
            out_pService = m_pSwallowPoiDbService;
            return (m_pSwallowPoiDbService != NULL);
        }
        
        void SwallowPoiDbServiceProvider::AddTransitionLoadedCallback(TransitionsLoadedCallback& callback)
        {
            m_transitionsLoadedCallbacks.AddCallback(callback);
        }
        
        void SwallowPoiDbServiceProvider::RemoveTransitionLoadedCallback(TransitionsLoadedCallback& callback)
        {
            m_transitionsLoadedCallbacks.RemoveCallback(callback);
        }
    }
}
