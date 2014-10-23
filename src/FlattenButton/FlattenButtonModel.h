// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IFlattenButtonModel.h"
#include "Rendering.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        class FlattenButtonModel : public IFlattenButtonModel, private Eegeo::NonCopyable
        {
            Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlattening;
            Eegeo::Helpers::CallbackCollection0 m_changedCallbacks;
            Eegeo::Helpers::ICallback0* m_pFlatteningModelChangedCallback;
            
        public:
            
            FlattenButtonModel(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);
            
            ~FlattenButtonModel();
            
            void HandleModelChanged();
            
            void Flatten();
            
            void Unflatten();
            
            bool GetFlattened() const;
            
            void InsertChangedCallback(Eegeo::Helpers::ICallback0& callback);
            
            void RemoveChangedCallback(Eegeo::Helpers::ICallback0& callback);
        };
    }
}
