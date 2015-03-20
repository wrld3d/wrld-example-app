// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsViewModel::MyPinDetailsViewModel(Eegeo::Helpers::TIdentity identity,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
                : m_openable(identity, reactionControllerModel)
            {

            }

            MyPinDetailsViewModel::~MyPinDetailsViewModel()
            {

            }

            bool MyPinDetailsViewModel::TryAcquireReactorControl()
            {
                return m_openable.TryAcquireReactorControl();
            }
            
            MyPins::SdkModel::MyPinModel::TPinIdType MyPinDetailsViewModel::GetMyPinId() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_id;
            }
            
            const std::string& MyPinDetailsViewModel::GetMyPinTitle() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_title;
            }
            
            const std::string& MyPinDetailsViewModel::GetMyPinDescription() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_description;
            }
            
            const std::string& MyPinDetailsViewModel::GetImagePath() const
            {
                Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
                return m_imagePath;
            }

            bool MyPinDetailsViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }

            void MyPinDetailsViewModel::Open(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                             const std::string& title,
                                             const std::string& description,
                                             const std::string& imagePath)
            {
                Eegeo_ASSERT(!IsOpen(), "Cannot open MyPinDetailsViewModel when already open.\n");
                
                if(m_openable.Open())
                {
                    m_id = pinId;
                    m_title = title;
                    m_description = description;
                    m_imagePath = imagePath;
                    m_openedCallbacks.ExecuteCallbacks();
                }
            }

            void MyPinDetailsViewModel::Close()
            {
                Eegeo_ASSERT(IsOpen(), "Cannot close SearchResultModel when view model when already closed.\n");

                {
                    const bool closed = m_openable.Close();
                    Eegeo_ASSERT(closed, "Failed to close");
                }

                m_closedCallbacks.ExecuteCallbacks();
            }

            OpenableControl::View::IOpenableControlViewModel& MyPinDetailsViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void MyPinDetailsViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void MyPinDetailsViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void MyPinDetailsViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void MyPinDetailsViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
        }
    }
}
