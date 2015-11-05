// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewModel.h"

#include <sstream>

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageViewModel::AboutPageViewModel(
                Eegeo::Helpers::TIdentity identity,
                Reaction::View::IReactionControllerModel& reactionControllerModel,
                const std::string& buildVersion,
                const std::string& platformVersion,
                const std::string& platformHash,
                const std::string& platformArchitecture,
                const std::string& aboutText)
                : m_openable(identity, reactionControllerModel)
                , m_buildVersion(buildVersion)
                , m_platformVersion(platformVersion)
                , m_platformHash(platformHash)
                , m_platformArchitecture(platformArchitecture)
                , m_aboutText(aboutText)
            {

            }

            AboutPageViewModel::~AboutPageViewModel()
            {

            }

            bool AboutPageViewModel::TryAcquireReactorControl()
            {
                return m_openable.TryAcquireReactorControl();
            }

            bool AboutPageViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }

            const std::string AboutPageViewModel::GetContent() const
            {
                const std::string DefaultBuildVersionString = "INSERT BUILD VERSION HERE";
                
                std::stringstream content;
                content << m_aboutText;
                
                if(m_buildVersion.find(DefaultBuildVersionString) == std::string::npos)
                {
                    content << "\n\nApplication build version: " + m_buildVersion;
                }
                
                content << "\n\nPlatform version: " + m_platformVersion
                        << "\nPlatform hash: " + m_platformHash
                        << "\nPlatform runtime arch: " + m_platformArchitecture
                        << "\n\n";
                return content.str();
            }

            void AboutPageViewModel::Open()
            {
                if(!IsOpen())
                {
                    if(m_openable.Open())
                    {
                        m_openedCallbacks.ExecuteCallbacks();
                    }
                }
            }

            void AboutPageViewModel::Close()
            {
                if(IsOpen())
                {
                    {
                        const bool closed = m_openable.Close();
                        Eegeo_ASSERT(closed, "Failed to close");
                    }

                    m_closedCallbacks.ExecuteCallbacks();
                }
            }

            OpenableControl::View::IOpenableControlViewModel& AboutPageViewModel::GetOpenableControl()
            {
                return m_openable;
            }

            void AboutPageViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }

            void AboutPageViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }

            void AboutPageViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }

            void AboutPageViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
        }
    }
}
