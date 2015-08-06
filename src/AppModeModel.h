// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppModeModel.h"
#include "Interiors.h"

namespace ExampleApp
{
    class AppModeModel : public IAppModeModel
    {
    public:
        AppModeModel(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel);
        ~AppModeModel();

        AppMode GetAppMode() const;

        void RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback);
        void UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

    private:
        void SetAppMode(AppMode appMode);

        Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;

        void OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
        Eegeo::Helpers::TCallback1<AppModeModel, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionModelChangedCallback;

        Eegeo::Helpers::CallbackCollection0 m_appModeChangedCallbacks;

        AppMode m_appMode;
    };
}