// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DeepLinkModel.h"
#include "ApplicationConfiguration.h"
#include "IFlattenButtonModel.h"



namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            class DeepLinkController: private Eegeo::NonCopyable
            {
            public:
                DeepLinkController(DeepLinkModel& deepLinkModel, FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel);
                ~DeepLinkController();
                void HandleDeepLinkOpen(const AppInterface::UrlData& data);
            private:
                DeepLinkModel& m_deepLinkModel;
                
                FlattenButton::SdkModel::IFlattenButtonModel& m_flattenButtonModel;
            };
        }
    }
}
