// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultSectionOrder.h"
#include "Interiors.h"
#include "AppCamera.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultSectionOrder : public ISearchResultSectionOrder
            {
            public:
                
                SearchResultSectionOrder(const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                         const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                        AppCamera::SdkModel::IAppCameraController& appCameraController);
                
                bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b);
                
            private:
                
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_interiorMarkerRepository;
                AppCamera::SdkModel::IAppCameraController& m_appCameraController;
            };
        }
    }
}