// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
}

- (id)initWithParams:(ExampleApp::InitialExperience::PreLoad::iOSInitialExperiencePreLoadModel *)pInitialExperiencePreLoadModel;

@end

@implementation PreLoadModelListener

- (id)initWithParams:(ExampleApp::InitialExperience::PreLoad::iOSInitialExperiencePreLoadModel *)pInitialExperiencePreLoadModel
{
	if(self = [super init])
	{
		self->m_pInitialExperiencePreLoadModel = pInitialExperiencePreLoadModel;

		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Pre-load San Francisco?"
		                      message:@"Select 'Yes' to pre-load data for the city of San Francisco. This message will not appear again."
		                      delegate:self
		                      cancelButtonTitle:@"No"
		                      otherButtonTitles:@"Yes", nil];


		[alert show];
		[alert release];
	}

	return self;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
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
			iOSInitialExperiencePreLoadModel::iOSInitialExperiencePreLoadModel(WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel,
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
				DestroyAlertListener();

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
				m_pAlertListener = [[PreLoadModelListener alloc] initWithParams:this];
			}
		}
	}
}
