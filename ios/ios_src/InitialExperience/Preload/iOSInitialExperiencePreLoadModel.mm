// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#import <UIKit/UIKit.h>
#include "iOSInitialExperiencePreLoadModel.h"
#include "IWorldAreaLoaderModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            class iOSInitialExperiencePreLoadModel;
        }
    }
}

@interface PreLoadModelListener : NSObject<UIAlertViewDelegate>
{
    ExampleApp::InitialExperience::PreLoad::iOSInitialExperiencePreLoadModel* m_pInitialExperiencePreLoadModel;
    bool m_handeled;
}

- (id)initWithParams:(ExampleApp::InitialExperience::PreLoad::iOSInitialExperiencePreLoadModel *)pInitialExperiencePreLoadModel;

@end

@implementation PreLoadModelListener

- (id)initWithParams:(ExampleApp::InitialExperience::PreLoad::iOSInitialExperiencePreLoadModel *)pInitialExperiencePreLoadModel
{
    if(self = [super init])
    {
        self->m_pInitialExperiencePreLoadModel = pInitialExperiencePreLoadModel;
        self->m_handeled = false;
        
        NSString* alertTitle = @"Pre-load San Francisco?";
        NSString* alertMessage = @"Select 'Yes' to pre-load data for the city of San Francisco. This message will not appear again.";
        NSString* noMessage = @"No";
        NSString* yesMessage = @"Yes";
        
        if([UIAlertController class])
        {
            UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle
                                                                           message:alertMessage
                                                                    preferredStyle:UIAlertControllerStyleAlert];
            
            UIAlertAction* openSiteAction = [UIAlertAction actionWithTitle:yesMessage
                                                                     style:UIAlertActionStyleDefault
                                                                   handler:^(UIAlertAction * action) { m_pInitialExperiencePreLoadModel->HandleDismiss(true); }];
            
            UIAlertAction* cancelAction = [UIAlertAction actionWithTitle:noMessage
                                                                   style:UIAlertActionStyleCancel
                                                                 handler:^(UIAlertAction * action) { m_pInitialExperiencePreLoadModel->HandleDismiss(false); }];
            
            [alert addAction:openSiteAction];
            [alert addAction:cancelAction];
            
            UIWindow *window = [[UIApplication sharedApplication] keyWindow];
            UIViewController *viewController = window.rootViewController;
            [viewController presentViewController:alert animated:YES completion:nil];
        }
        else
        {
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                            message:alertMessage
                                                           delegate:self
                                                  cancelButtonTitle:noMessage
                                                  otherButtonTitles:yesMessage, nil];
            
            [alert show];
            [alert release];
        }
    }

    return self;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(m_handeled)
    {
        return;
    }
    m_handeled = true;
    
    bool shouldPreload = false;

    if (buttonIndex == 1)
    {
        shouldPreload = true;
    }

    m_pInitialExperiencePreLoadModel->HandleDismiss(shouldPreload);
}

@end


namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            iOSInitialExperiencePreLoadModel::iOSInitialExperiencePreLoadModel(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                    PersistentSettings::IPersistentSettingsModel& persistentSettings)
                : InitialExperiencePreLoadModelBase(worldAreaLoaderModel, persistentSettings)
                , m_pAlertListener(NULL)
            {

            }

            iOSInitialExperiencePreLoadModel::~iOSInitialExperiencePreLoadModel()
            {
                DestroyAlertListener();
            }

            void iOSInitialExperiencePreLoadModel::DestroyAlertListener()
            {
                if(m_pAlertListener != NULL)
                {
                    PreLoadModelListener* pAlertListener = static_cast<PreLoadModelListener*>(m_pAlertListener);
                    [pAlertListener release];
                    m_pAlertListener = NULL;
                }
            }

            void iOSInitialExperiencePreLoadModel::HandleDismiss(bool shouldPreload)
            {
                if(shouldPreload)
                {
                    PrecacheRegion();
                }
                else
                {
                    Complete();
                }
            }

            void iOSInitialExperiencePreLoadModel::ShowOptions()
            {
                DestroyAlertListener();
                m_pAlertListener = [[PreLoadModelListener alloc] initWithParams:this];
            }
        }
    }
}
