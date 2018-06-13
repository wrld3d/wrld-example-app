#ifndef WRLDNavModelObserverCpp_h
#define WRLDNavModelObserverCpp_h

#ifdef __cplusplus

#include <string>
#include "WrldNav/WrldNav.h"

class WRLDNavModelObserverCpp 
{
public:
    WRLDNavModelObserverCpp();
    
    virtual ~WRLDNavModelObserverCpp();

    void registerObserver(const std::string& observerKey);
    
    void setNavModel(::WRLDNavModel* navModel);
    
    WRLDNavModel* navModel()const;

    virtual void modelSet();
    
    virtual void changeReceived(const std::string& keyPath);
    
    virtual void eventReceived(WRLDNavEvent key);
    
private:
    struct Private;
    Private* d;
};

#endif

#endif
