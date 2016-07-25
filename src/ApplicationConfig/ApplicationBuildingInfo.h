//
//  ApplicationBuildingInfo.hpp
//  LDCExampleApp
//
//  Created by Sohail Khan on 5/24/16.
//
//



#include <stdio.h>
#include <string>



namespace ExampleApp
{
    namespace ApplicationConfig
    {
        class ApplicationBuildingInfo {
        
        private:
            const std::string m_senionMapKey;
            const std::string m_senionMapCustomerID;
            const std::string m_interiorID;
            
        public:
            ApplicationBuildingInfo(const std::string senionMapKey,const std::string senionMapCustomerID,const std::string interiorID);
            
            
            
            const std::string& SenionMapKey() const;
            const std::string& SenionMapCustomerID() const;
            const std::string& InteriorID() const;

        };
    
    }
}
