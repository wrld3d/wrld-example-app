// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageViewModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                TourFullScreenImageViewModel::TourFullScreenImageViewModel()
                : m_image("")
                , m_message("")
                , m_isActive(false)
                {
                    
                }
                
                TourFullScreenImageViewModel::~TourFullScreenImageViewModel()
                {
                    
                }
                
                const std::string& TourFullScreenImageViewModel::GetAsset() const
                {
                    Eegeo_ASSERT(m_isActive);
                    return m_image;
                }
                
                const std::string& TourFullScreenImageViewModel::GetMessage() const
                {
                    Eegeo_ASSERT(m_isActive);
                    return m_message;
                }
                
                void TourFullScreenImageViewModel::BeginFullScreenImageCeremony(const std::string& image,
                                                                                const std::string& message)
                {
                    Eegeo_ASSERT(!m_isActive);
                    m_image = image;
                    m_message = message;
                    m_isActive = true;
                    m_beginCeremonyCallbacks.ExecuteCallbacks();
                }
                
                void TourFullScreenImageViewModel::EndFullScreenImageCeremony()
                {
                    Eegeo_ASSERT(m_isActive);
                    m_image = "";
                    m_message = "";
                    m_isActive = false;
                    m_endCeremonyCallbacks.ExecuteCallbacks();
                }
                
                void TourFullScreenImageViewModel::InsertBeginCeremonyCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_beginCeremonyCallbacks.AddCallback(callback);
                }
                
                void TourFullScreenImageViewModel::RemoveBeginCeremonyCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_beginCeremonyCallbacks.RemoveCallback(callback);
                }
                
                void TourFullScreenImageViewModel::InsertEndCeremonyCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_endCeremonyCallbacks.AddCallback(callback);
                }
                
                void TourFullScreenImageViewModel::RemoveEndCeremonyCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_endCeremonyCallbacks.RemoveCallback(callback);
                }
            }
        }
    }
}
