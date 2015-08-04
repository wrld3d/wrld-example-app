// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonModel.h"
#include "IMapModeModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            FlattenButtonModel::FlattenButtonModel(MapMode::SdkModel::IMapModeModel& mapModeModel)
            : m_mapModeModel(mapModeModel)
            , m_onMapModeChangedCallback(this, &FlattenButtonModel::OnMapModeChanged)
            {
                m_mapModeModel.AddMapModeChangedCallback(m_onMapModeChangedCallback);
            }

            FlattenButtonModel::~FlattenButtonModel()
            {
                m_mapModeModel.RemoveMapModeChangedCallback(m_onMapModeChangedCallback);
            }

            void FlattenButtonModel::Flatten()
            {
                m_mapModeModel.SetInMapMode(true);
            }

            void FlattenButtonModel::Unflatten()
            {
                m_mapModeModel.SetInMapMode(false);
            }

            bool FlattenButtonModel::GetFlattened() const
            {
                return m_mapModeModel.IsInMapMode();
            }

            void FlattenButtonModel::InsertChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_changedCallbacks.AddCallback(callback);
            }

            void FlattenButtonModel::RemoveChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_changedCallbacks.RemoveCallback(callback);
            }

            void FlattenButtonModel::OnMapModeChanged()
            {
                m_changedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
