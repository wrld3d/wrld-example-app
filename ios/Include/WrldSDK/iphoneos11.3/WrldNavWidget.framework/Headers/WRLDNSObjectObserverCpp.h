#ifndef WRLDNSObjectObserverCpp_h
#define WRLDNSObjectObserverCpp_h

#ifdef __cplusplus

#include <string>
#include "WrldNav/WrldNav.h"

class WRLDNSObjectObserverCpp
{
public:
    WRLDNSObjectObserverCpp();
    
    virtual ~WRLDNSObjectObserverCpp();
    
    void setObject(NSObject* object);
    
    void registerObserver(const std::string& observerKey);
        
    virtual void changeReceived(const std::string& keyPath);
    
private:
    struct Private;
    Private* d;
};

#endif

#endif
