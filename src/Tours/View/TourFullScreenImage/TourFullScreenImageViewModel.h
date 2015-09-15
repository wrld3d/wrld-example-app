// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ITourFullScreenImageViewModel.h"
#include "Tours.h"
#include "CallbackCollection.h"
#include "TourModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class TourFullScreenImageViewModel : public ITourFullScreenImageViewModel, private Eegeo::NonCopyable
                {
                public:
                    TourFullScreenImageViewModel();
                    
                    ~TourFullScreenImageViewModel();
                    
                    const std::string& GetAsset() const;
                    
                    const std::string& GetMessage() const;
                    
                    void BeginFullScreenImageCeremony(const std::string& image,
                                                      const std::string& message);
                    
                    void EndFullScreenImageCeremony();
                    
                    void InsertBeginCeremonyCallback(Eegeo::Helpers::ICallback0& callback);
                    
                    void RemoveBeginCeremonyCallback(Eegeo::Helpers::ICallback0& callback);
                    
                    void InsertEndCeremonyCallback(Eegeo::Helpers::ICallback0& callback);
                    
                    void RemoveEndCeremonyCallback(Eegeo::Helpers::ICallback0& callback);
                    
                private:
                    std::string m_image;
                    std::string m_message;
                    bool m_isActive;
                    Eegeo::Helpers::CallbackCollection0 m_beginCeremonyCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_endCeremonyCallbacks;
                };
            }
        }
    }
}
