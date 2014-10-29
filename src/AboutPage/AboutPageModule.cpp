// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageModule.h"
#include "AboutPageModel.h"
#include "AboutPageViewModel.h"
#include "EegeoWorld.h"

namespace
{
    const std::string AboutPageText = "Powered by eeGeo's 3D Mapping Platform"
    "\n\nEEGEO DUNDEE"
    "\n\nTechnical Director"
    "\nOliver Norton"
    
    "\n\nTechnical Lead"
    "\nTim Jenks"
    
    "\n\nSenior Software Engineers"
    "\nMalcolm Brown"
    "\nJonty Dawson"
    "\nSalvador Lopez"
    "\nScott Murray"
    "\nMark Simpson"
    
    "\n\nJunior Software Engineer"
    "\nIan Hutchinson"
    
    "\n\nSenior Artists"
    "\nMike McLarty"
    "\nGary Thomson"
    
    "\n\nSystem Test Lead"
    "\nDavid Murdoch"
    
    "\n\nSenior System Tester"
    "\nRyan Reid"
    
    "\n\nSystem Tester"
    "\nMichael Celej"
    
    "\n\n\nEEGEO SAN FRANCISCO"
    "\n\nBusiness Development Director"
    "\nBart Denny"
    
    "\n\n\nEEGEO LONDON"
    "\n\nExecutive Chairman"
    "\nIan Hetherington"
    
    "\n\nChief Financial Officer"
    "\nJeremy Copp\n"
    
    "\n\nSource data courtesy of:"

    "\n\nTomTom Global Content. ©2006-2014 TomTom."
    "\n\nOrdnance Survey MasterMap & NTF © Crown copyright and database rights 2014 Ordnance Survey 100050219."
    "\n\nNASA SRTM and Bluemarble - NASA Visible Earth."
    "\n\nNASA ASTER 30m DTM - ASTER Global DEM data obtained from https://lpdaac.usgs.gov, maintained by the NASA Land Processes Distributed Active Archive Center (LP DAAC) at the USGS/Earth Resources Observation and Science (EROS) Center, Sioux Falls, South Dakota. 2012. ASTER GDEM is a product of METI and NASA."
    "\n\nU.S. Geological Survey."
    "\n\nEuropean Environment Agency."
    "\n\nNaturalVue Copyright MDA Information Systems, Inc."
    "\n\nGeoNames (www.geonames.org)."
    "\n\nMade with Natural Earth."
    "\n\nSeattle Public Utilities (www.seattle.gov/gis)."
    "\n\nCity of Chicago (www.cityofchicago.org)."
    "\n\nRLIS Discovery (rlisdiscovery.oregonmetro.gov)."
    "\n\nGeoBase Canadian Digital Elevation Data - GeoBase®."
    "\n\nCanVec LCC-2000	- Natural Resources Canada."
    "\n\nOpen Street Map Buildings & Structures © OpenStreetMap contributors - More information at http://sdk.eegeo.com/osm."
    ;
}

namespace ExampleApp
{
    namespace AboutPage
    {
        AboutPageModule::AboutPageModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                         Reaction::IReactionControllerModel& reactionControllerModel)
        {
            m_pAboutPageModel = Eegeo_NEW(AboutPageModel)(EEGEO_PLATFORM_VERSION_NUMBER, EEGEO_PLATFORM_VERSION_HASH, AboutPageText);
            m_pAboutPageViewModel = Eegeo_NEW(AboutPageViewModel)(identityProvider.GetNextIdentity(), reactionControllerModel);
        }
        
        AboutPageModule::~AboutPageModule()
        {
            Eegeo_DELETE m_pAboutPageViewModel;
            Eegeo_DELETE m_pAboutPageModel;
        }
        
        IAboutPageModel& AboutPageModule::GetAboutPageModel() const
        {
            return *m_pAboutPageModel;
        }
        
        IAboutPageViewModel& AboutPageModule::GetAboutPageViewModel() const
        {
            return *m_pAboutPageViewModel;
        }
        
        OpenableControlViewModel::IOpenableControlViewModel& AboutPageModule::GetObservableOpenableControl() const
        {
            return m_pAboutPageViewModel->GetOpenableControl();
        }
    }
}
