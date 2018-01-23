// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



#include "InteriorExplorerConnectionController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorExplorerConnectionController::InteriorExplorerConnectionController(InteriorExplorerConnectionChangedObserver& interiorExplorerConnectionChangedObserver)
            :m_pInteriorExplorerConnectionChangedObserver(interiorExplorerConnectionChangedObserver)
            ,m_hasEjectedUser(false)
            ,m_ssidTimeout(60.f)
            ,m_timeSinceAuthorisedForInterior(0.f)
            {
            }

            InteriorExplorerConnectionController::~InteriorExplorerConnectionController()
            {
            }

            void InteriorExplorerConnectionController::Update(float dt)
            {
                if (m_pInteriorExplorerConnectionChangedObserver.AuthorisedForCurrentInterior())
                {
                    m_hasEjectedUser = false;
                    m_timeSinceAuthorisedForInterior = 0.f;
                }
                else
                {
                    m_timeSinceAuthorisedForInterior += dt;
                }

                if (m_timeSinceAuthorisedForInterior >= m_ssidTimeout)
                {
                    if (!m_hasEjectedUser)
                    {
                        m_hasEjectedUser = true;
                        m_pInteriorExplorerConnectionChangedObserver.OnWifiDisconnected();
                    }
                }
            }
        }
    }
}
