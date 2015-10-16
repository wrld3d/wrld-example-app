// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbServiceProvider.h"

#include "SwallowPoiDbCombinedService.H"
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
            
            pSwallowPoiDbService->GetTransitionResults(transitionResults);
            
            m_transitionsLoadedCallbacks.ExecuteCallbacks(transitionResults);
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
