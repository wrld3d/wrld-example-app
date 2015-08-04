// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IFlattenButtonModel.h"
#include "CallbackCollection.h"
#include "WeatherMenu.h"
#include "MapMode.h"
#include <string>

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            class FlattenButtonModel : public IFlattenButtonModel, private Eegeo::NonCopyable
            {
                MapMode::SdkModel::IMapModeModel& m_mapModeModel;

                Eegeo::Helpers::CallbackCollection0 m_changedCallbacks;
                Eegeo::Helpers::TCallback0<FlattenButtonModel> m_onMapModeChangedCallback;

                void OnMapModeChanged();

            public:

                FlattenButtonModel(MapMode::SdkModel::IMapModeModel& mapModeModel);

                ~FlattenButtonModel();

                void Flatten();

                void Unflatten();

                bool GetFlattened() const;

                void InsertChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveChangedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
