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
        ApplicationBuildingInfo::ApplicationBuildingInfo(const std::string senionMapKey,const std::string senionMapCustomerID,const std::string interiorID, const std::map<int,int> senionFloorMap): m_senionMapKey(senionMapKey),
                                    m_senionMapCustomerID(senionMapCustomerID),
                                    m_interiorID(interiorID),
                                    m_senionfloorMap(senionFloorMap)
        {
        
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
        
        const std::map<int,int>& ApplicationBuildingInfo::SenionFloorMap() const{
            return m_senionfloorMap;
        }
    }
}