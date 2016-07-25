//
//  ApplicationBuildingInfo.cpp
//  LDCExampleApp
//
//  Created by Sohail Khan on 5/24/16.
//
//

#include "ApplicationBuildingInfo.h"


namespace ExampleApp
{
    namespace ApplicationConfig
    {
        ApplicationBuildingInfo::ApplicationBuildingInfo(const std::string senionMapKey,const std::string senionMapCustomerID,const std::string interiorID): m_senionMapKey(senionMapKey),m_senionMapCustomerID(senionMapCustomerID),m_interiorID(interiorID){
        
        }
        
        
        
        const std::string& ApplicationBuildingInfo::SenionMapKey() const{
            return m_senionMapKey;
        }
        
        const std::string& ApplicationBuildingInfo::SenionMapCustomerID() const{
            return m_senionMapCustomerID;
        }
        
        const std::string& ApplicationBuildingInfo::InteriorID() const{
            return m_interiorID;
        }
    }
}