// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>

#include "CallbackCollection.h"
#include "Types.h"
#include "ICallback.h"

#include "SearchResultModel.h"
#include "SwallowPoiDb.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        class SwallowPoiDbServiceProvider : public Eegeo::Helpers::TCallback1<SwallowPoiDbServiceProvider, SwallowPoiDbCombinedService*>, Eegeo::NonCopyable
        {
        public:
            typedef Eegeo::Helpers::ICallback1<const std::vector<Search::SdkModel::SearchResultModel>&> TransitionsLoadedCallback;
            
            SwallowPoiDbServiceProvider();
            
            ~SwallowPoiDbServiceProvider();
            
            bool TryGetSwallowPoiDbService(SwallowPoiDbCombinedService*& out_pService) const;
            
            void SwallowPoiDbWebLoaderCompleted(SwallowPoiDbCombinedService*& pSwallowPoiDbService);
            
            void AddTransitionLoadedCallback(TransitionsLoadedCallback& callback);
            void RemoveTransitionLoadedCallback(TransitionsLoadedCallback& callback);
            
        private:
            SwallowPoiDbCombinedService* m_pSwallowPoiDbService;
            
            Eegeo::Helpers::CallbackCollection1<const std::vector<Search::SdkModel::SearchResultModel>&> m_transitionsLoadedCallbacks;
        };
    }
}