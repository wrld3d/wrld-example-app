// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once
#include "DeepLink.h"
#include "CameraTransitions.h"
#include "IAlertBoxFactory.h"
#include "IFlattenButtonModel.h"
#include "SelectFirstResultSearchService.h"
#include "DeepLinkConfigHandler.h"
#include "DeepLinkSearchHandler.h"
#include "MapsceneLoader.h"

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkModule: private Eegeo::NonCopyable
            {
            public:

                DeepLinkModule(
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                    FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel,
                    Search::SelectFirstResult::SdkModel::SelectFirstResultSearchService& selectFirstResultSearchService,
                    Mapscene::SdkModel::MapsceneLoader& mapsceneLoader);

                ~DeepLinkModule();
                DeepLinkController& GetDeepLinkController();
            private:
                DeepLinkSearchHandler* m_pDeepLinkSearchHandler;
                DeepLinkConfigHandler* m_pDeepLinkConfigHandler;
                DeepLinkModel* m_pDeepLinkModel;
                DeepLinkController* m_pDeepLinkController;
            };
        }
    }
}
