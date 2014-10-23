// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundViewController.h"
#include "Types.h"
#include "ModalBackgroundView.h"
#include "IModalityModel.h"
#include "ICallback.h"

class ModalBackgroundViewControllerInterop
{
    ModalBackgroundViewController* m_pInstance;
    ExampleApp::Modality::IModalityModel& m_modalityModel;
    Eegeo::Helpers::ICallback0* m_pModalityChangedCallback;
    
    void ModalityChangedCallback()
    {
        [m_pInstance handleOpenStateChanged:m_modalityModel.GetModality()];
    }
    
public:
    ModalBackgroundViewControllerInterop(ModalBackgroundViewController* pInstance,
                                         ExampleApp::Modality::IModalityModel& modalityModel)
    : m_pInstance(pInstance)
    , m_modalityModel(modalityModel)
    , m_pModalityChangedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<ModalBackgroundViewControllerInterop>)(this, &ModalBackgroundViewControllerInterop::ModalityChangedCallback))
    {
        m_modalityModel.InsertModalityChangedCallback(*m_pModalityChangedCallback);
    }
    
    ~ModalBackgroundViewControllerInterop()
    {
        m_modalityModel.RemoveModalityChangedCallback(*m_pModalityChangedCallback);
        
        Eegeo_DELETE m_pModalityChangedCallback;
    }
};


@implementation ModalBackgroundViewController

- (id)initWithParams:(ExampleApp::Modality::IModalityModel*) pModalityModel
{
    if(self = [super init])
    {
        m_pModalityModel = pModalityModel;
        m_pInterop = Eegeo_NEW(ModalBackgroundViewControllerInterop)(self, *m_pModalityModel);
        
        self.pModalBackgroundView = [[[ModalBackgroundView alloc] initWithController:self] autorelease];
        [self.pModalBackgroundView  setFrame:[self view].bounds];
        self.view = self.pModalBackgroundView;
        
        [self.pModalBackgroundView setActiveStateToIntermediateValue:m_pModalityModel->GetModality()];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pModalBackgroundView release];
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) handleOpenStateChanged:(float)openState
{
    if(openState == 1.f)
    {
        [self.pModalBackgroundView setFullyActive];
    }
    else if(openState == 0.f)
    {
        [self.pModalBackgroundView setFullyInactive];
    }
    else
    {
        [self.pModalBackgroundView setActiveStateToIntermediateValue:openState];
    }
}

@end


