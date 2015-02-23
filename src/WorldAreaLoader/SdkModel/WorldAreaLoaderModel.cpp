// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldAreaLoaderModel.h"
#include "PrecacheService.h"

namespace ExampleApp
{
    namespace WorldAreaLoader
    {
        namespace SdkModel
        {
            WorldAreaLoaderModel::WorldAreaLoaderModel(Eegeo::Web::PrecacheService& precacheService)
                : m_precacheService(precacheService)
                , m_preloadInProgress(precacheService.CurrentlyPrecaching())
                , m_preloadCompletedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<WorldAreaLoaderModel>(this, &WorldAreaLoaderModel::HandlePreloadServiceEvent)))
                , m_preloadCancelledCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<WorldAreaLoaderModel>(this, &WorldAreaLoaderModel::HandlePreloadServiceEvent)))
            {
                m_precacheService.InsertPrecacheCompletedCallback(*m_preloadCompletedCallback);
                m_precacheService.InsertPrecacheCancelledCallback(*m_preloadCancelledCallback);
            }

            WorldAreaLoaderModel::~WorldAreaLoaderModel()
            {
                m_precacheService.RemovePrecacheCompletedCallback(*m_preloadCompletedCallback);
                m_precacheService.RemovePrecacheCancelledCallback(*m_preloadCancelledCallback);

                Eegeo_DELETE m_preloadCompletedCallback;
                Eegeo_DELETE m_preloadCancelledCallback;
            }

            float WorldAreaLoaderModel::PercentCompleted() const
            {
                return m_precacheService.PercentCompleted();
            }

            bool WorldAreaLoaderModel::CurrentlyPreloading() const
            {
                return m_precacheService.CurrentlyPrecaching();
            }

            bool WorldAreaLoaderModel::IsCancelling() const
            {
                return m_precacheService.IsCancelling();
            }

            bool WorldAreaLoaderModel::CanPreload(double altitude) const
            {
                return m_precacheService.CanPrecache(altitude);
            }

            void WorldAreaLoaderModel::CancelPreload()
            {
                return m_precacheService.CancelPrecaching();
            }

            void WorldAreaLoaderModel::PreloadResourcesInVolume(Eegeo::Streaming::IStreamingVolume& volume)
            {
                Eegeo_ASSERT(!m_preloadInProgress, "Already pre-loading, cancel current pre-load before starting another.\n")
                m_preloadInProgress = true;
                m_precacheService.Precache(volume);
                m_preloadStartedCallbacks.ExecuteCallbacks();
            }

            void WorldAreaLoaderModel::ObserveUnderlyingService()
            {
                if(m_preloadInProgress && !CurrentlyPreloading())
                {
                    m_preloadInProgress = false;
                    m_preloadCompletedCallbacks.ExecuteCallbacks();
                }

                m_preloadInProgress = CurrentlyPreloading();
            }

            void WorldAreaLoaderModel::InsertPreloadStartedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_preloadStartedCallbacks.AddCallback(callback);
            }

            void WorldAreaLoaderModel::RemovePreloadStartedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_preloadStartedCallbacks.RemoveCallback(callback);
            }

            void WorldAreaLoaderModel::InsertPreloadCompleteCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_preloadCompletedCallbacks.AddCallback(callback);
            }

            void WorldAreaLoaderModel::RemovePreloadCompleteCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_preloadCompletedCallbacks.RemoveCallback(callback);
            }

            void WorldAreaLoaderModel::HandlePreloadServiceEvent()
            {
                ObserveUnderlyingService();
            }
        }
    }
}
