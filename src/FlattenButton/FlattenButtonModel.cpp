// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FlattenButtonModel.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        FlattenButtonModel::FlattenButtonModel(Eegeo::Rendering::EnvironmentFlatteningService& flatteningService)
        : m_environmentFlattening(flatteningService)
        , m_pFlatteningModelChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<FlattenButtonModel>)(this, &FlattenButtonModel::HandleModelChanged))
        {
            m_environmentFlattening.InsertChangedCallback(*m_pFlatteningModelChangedCallback);
        }
        
        FlattenButtonModel::~FlattenButtonModel()
        {
            m_environmentFlattening.RemoveChangedCallback(*m_pFlatteningModelChangedCallback);
            Eegeo_DELETE m_pFlatteningModelChangedCallback;
        }
        
        void FlattenButtonModel::HandleModelChanged()
        {
            m_changedCallbacks.ExecuteCallbacks();
        }
        
        void FlattenButtonModel::Flatten()
        {
            if(m_environmentFlattening.IsFlattened())
            {
                return;
            }
            m_environmentFlattening.SetIsFlattened(true);
            m_changedCallbacks.ExecuteCallbacks();
        }
        
        void FlattenButtonModel::Unflatten()
        {
            if(!m_environmentFlattening.IsFlattened())
            {
                return;
            }
            m_environmentFlattening.SetIsFlattened(false);
            m_changedCallbacks.ExecuteCallbacks();
        }
        
        bool FlattenButtonModel::GetFlattened() const
        {
            return m_environmentFlattening.IsFlattened();
        }
        
        void FlattenButtonModel::InsertChangedCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_changedCallbacks.AddCallback(callback);
        }
        
        void FlattenButtonModel::RemoveChangedCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_changedCallbacks.RemoveCallback(callback);
        }
    }
}
