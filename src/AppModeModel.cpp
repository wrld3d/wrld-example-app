// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppModeModel.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    AppModeModel::AppModeModel(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel)
    : m_interiorSelectionModel(interiorSelectionModel)
    , m_interiorSelectionModelChangedCallback(this, &AppModeModel::OnInteriorSelectionModelChanged)
    , m_appMode(WorldMode)
    {
        m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
    }

    AppModeModel::~AppModeModel()
    {
        m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionModelChangedCallback);
    }

    void AppModeModel::OnInteriorSelectionModelChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
    {
        AppMode newAppMode = m_interiorSelectionModel.IsInteriorSelected() ? InteriorMode : WorldMode;
        SetAppMode(newAppMode);
    }

    void AppModeModel::RegisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
    {
        m_appModeChangedCallbacks.AddCallback(callback);
    }

    void AppModeModel::UnregisterAppModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
    {
        m_appModeChangedCallbacks.RemoveCallback(callback);
    }

    AppMode AppModeModel::GetAppMode() const
    {
        return m_appMode;
    }

    void AppModeModel::SetAppMode(AppMode appMode)
    {
        if (m_appMode != appMode)
        {
            m_appMode = appMode;
            m_appModeChangedCallbacks.ExecuteCallbacks();
        }
    }
}