// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MapModeModel.h"

namespace ExampleApp
{
    namespace MapMode
    {
        namespace SdkModel
        {
            MapModeModel::MapModeModel()
            : m_inMapMode(false)
            {

            }

            MapModeModel::~MapModeModel()
            {

            }

            bool MapModeModel::IsInMapMode() const
            {
                return m_inMapMode;
            }

            void MapModeModel::SetInMapMode(bool inMapMode)
            {
                if (m_inMapMode != inMapMode)
                {
                    m_inMapMode = inMapMode;
                    m_mapModeChangedCallbacks.ExecuteCallbacks();
                }
            }

            void MapModeModel::AddMapModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_mapModeChangedCallbacks.AddCallback(callback);
            }

            void MapModeModel::RemoveMapModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_mapModeChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}