// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#import "SenionLabModule.h"
#include "InteriorSelectionModel.h"
#import <sys/utsname.h>

namespace ExampleApp
{
    namespace SenionLab
    {

        SenionLabModule::SenionLabModule(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *deviceModel,
                                         ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                         const std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>&buildingsInfo): m_deviceModel(deviceModel),
                                                                                                                                    m_appModeChangedCallback(this, &SenionLabModule::OnAppModeChanged),
                                                                                                                                    m_appModeModel(appModeModel),
                                                                                                                                    m_interiorSelectionModel(interiorSelectionModel),                                                                                                                                    m_buildingsInfoList(buildingsInfo)
        {
            m_pLoctionManager = nil;
            m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);

        }
        
        SenionLabModule::~SenionLabModule()
        {
            [m_pLoctionManager release];
            m_pLoctionManager = nil;
            
        }
        
        void SenionLabModule::OnAppModeChanged()
        {
            
            if (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
            {
                
                Eegeo::Resources::Interiors::InteriorId builingID = m_interiorSelectionModel.GetSelectedInteriorId();
                InitlizeSenionLocationManagerWithInteriorID(getBuildingInfo(builingID));
            }
        }
        
        ExampleApp::ApplicationConfig::ApplicationBuildingInfo* SenionLabModule::getBuildingInfo(Eegeo::Resources::Interiors::InteriorId interiorID)
        {
            
            ExampleApp::ApplicationConfig::ApplicationBuildingInfo *respectiveBuilding = NULL;
            for(std::vector<ExampleApp::ApplicationConfig::ApplicationBuildingInfo*>::const_iterator it = m_buildingsInfoList.begin(); it != m_buildingsInfoList.end(); ++it)
            {
                
                if ((*it)->InteriorID().compare(interiorID.Value()) == 0)
                {
                    respectiveBuilding = *it;
                    break;
                    
                }
            }
            return respectiveBuilding;
        }
        
        BOOL isBluetoothSupported(NSString *deviceName)   {
            
            if([deviceName hasPrefix:@"iPad2"])
            {
                return false;
            }
            
            return true;
        }

        void SenionLabModule::InitlizeSenionLocationManagerWithInteriorID(ExampleApp::ApplicationConfig::ApplicationBuildingInfo *respectiveBuilding)
        {
            
            if (respectiveBuilding == NULL)
                return;            
            
            if (m_pLoctionManager)
            {
                [m_pLoctionManager release];
                m_pLoctionManager = nil;

            }
            Eegeo::Resources::Interiors::InteriorId builingID(std::string(respectiveBuilding->InteriorID()));
            
            struct utsname systemInfo;
            uname(&systemInfo);
            NSString *deviceModel = [NSString stringWithCString:systemInfo.machine
                                                   encoding:NSUTF8StringEncoding];
            
            // Currently its a bit of hack for iPad 2. Unable to fetch the blue tooth version
            
            if(isBluetoothSupported(deviceModel))
            {
                m_pLoctionManager = [[SenionLabLocationManager alloc] initWithAvtarModule:m_deviceModel senionMapKey:[NSString stringWithCString:respectiveBuilding->SenionMapKey().c_str() encoding:[NSString defaultCStringEncoding]] senionCustomerID:[NSString stringWithCString:respectiveBuilding->SenionMapCustomerID().c_str() encoding:[NSString defaultCStringEncoding]] builidingID:builingID];
            }
            else
            {
                UIAlertView *pUnsupportedPopUp = [[UIAlertView alloc] initWithTitle:@"Alert" message:@"Senion navigation is not available due to unsupported bluetooth hardware." delegate:nil cancelButtonTitle:@"Cancel" otherButtonTitles: nil];
                [pUnsupportedPopUp show];
                [pUnsupportedPopUp release];
            }
        }
        

        
    }
}
