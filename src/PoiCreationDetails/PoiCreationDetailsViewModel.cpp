// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsViewModel.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        PoiCreationDetailsViewModel::PoiCreationDetailsViewModel(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel)
        : m_openable(identity, reactionControllerModel)
        {
            
        }
        
        PoiCreationDetailsViewModel::~PoiCreationDetailsViewModel()
        {
            
        }
        
        bool PoiCreationDetailsViewModel::TryAcquireReactorControl()
        {
            return m_openable.TryAcquireReactorControl();
        }
        
        bool PoiCreationDetailsViewModel::IsOpen() const
        {
            return m_openable.IsFullyOpen();
        }
        
        void PoiCreationDetailsViewModel::Open()
        {
            if(!IsOpen())
            {
                if(m_openable.Open())
                {
                    m_openedCallbacks.ExecuteCallbacks();
                }
            }
        }
        
        void PoiCreationDetailsViewModel::Close()
        {
            if(IsOpen())
            {
                Eegeo_ASSERT(m_openable.Close());
                m_closedCallbacks.ExecuteCallbacks();
            }
        }
        
        OpenableControlViewModel::IOpenableControlViewModel& PoiCreationDetailsViewModel::GetOpenableControl()
        {
            return m_openable;
        }
        
        void PoiCreationDetailsViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
        {
            m_openedCallbacks.AddCallback(openedCallback);
        }
        
        void PoiCreationDetailsViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
        {
            m_openedCallbacks.RemoveCallback(openedCallback);
        }
        
        void PoiCreationDetailsViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
        {
            m_closedCallbacks.AddCallback(closedCallback);
        }
        
        void PoiCreationDetailsViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
        {
            m_closedCallbacks.RemoveCallback(closedCallback);
        }
    }
}
