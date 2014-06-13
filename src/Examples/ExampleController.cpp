// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ExampleController.h"

using namespace Examples;

ExampleController::ExampleController(Eegeo::EegeoWorld& world,
                                     IExampleControllerView& view)
	: m_world(world)
	, m_pCurrentExample(NULL)
	, m_currentExampleFactoryIndex(-1)
	, m_view(view)
	, m_nextExampleHandler(this, &ExampleController::ActivateNext)
	, m_previousExampleHandler(this, &ExampleController::ActivatePrevious)
	, m_selectedExampleChangedHandler(this, &ExampleController::UpdateSelectedExample)
	, m_uiVisible(false)
{
	m_view.AddSelectNextExampleHandler(m_nextExampleHandler);
	m_view.AddSelectPreviousExampleHandler(m_previousExampleHandler);
	m_view.AddExampleSelectedHandler(m_selectedExampleChangedHandler);
}

ExampleController::~ExampleController()
{
	m_view.RemoveSelectNextExampleHandler(m_nextExampleHandler);
	m_view.RemoveSelectPreviousExampleHandler(m_previousExampleHandler);
	m_view.RemoveExampleSelectedHandler(m_selectedExampleChangedHandler);

	DestroyCurrentExample();

	for(size_t i = 0; i < m_factories.size(); ++ i)
	{
		Eegeo_DELETE m_factories[i];
	}

	m_factories.clear();
}

std::vector<std::string> ExampleController::GetExampleNames() const
{
	std::vector<std::string> result;

	for(size_t i = 0; i < m_factories.size(); ++ i)
	{
		result.push_back(m_factories[i]->ExampleName());
	}

	return result;
}

void ExampleController::RefreshExample()
{
	DestroyCurrentExample();

	m_pCurrentExample = m_factories[m_currentExampleFactoryIndex]->CreateExample();

	if(m_pCurrentExample != NULL)
	{
		m_pCurrentExample->Start();
		m_pCurrentExample->EarlyUpdate(0.f);
		m_pCurrentExample->Update(0.f);
		m_view.SetCurrentExampleName(m_pCurrentExample->Name());
	}
}

void ExampleController::UpdateSelectedExample()
{
	std::string selectedExampleName = m_view.GetSelectedExample();

	for(size_t i = 0; i < m_factories.size(); ++ i)
	{
		if(m_factories[i]->ExampleName() == selectedExampleName && i != m_currentExampleFactoryIndex)
		{
			m_currentExampleFactoryIndex = i;
			RefreshExample();
			return;
		}
	}
}

void ExampleController::ActivatePrevious()
{
	if(m_factories.size() == 0)
	{
		return;
	}

	if(--m_currentExampleFactoryIndex < 0)
	{
		m_currentExampleFactoryIndex = m_factories.size() - 1;
	}

	RefreshExample();
}

void ExampleController::ActivateNext()
{
	if(m_factories.size() == 0)
	{
		return;
	}

	if(++m_currentExampleFactoryIndex > (m_factories.size()-1))
	{
		m_currentExampleFactoryIndex = 0;
	}

	RefreshExample();
}

void ExampleController::EarlyUpdate(float dt,
                                    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCamera,
                                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
{
	if(m_pCurrentExample != NULL)
	{
		m_pCurrentExample->EarlyUpdate(dt);
		m_pCurrentExample->UpdateCamera(&globeCamera, &globeCameraTouchController, dt);
		m_pCurrentExample->AfterCameraUpdate();
	}
}

void ExampleController::Update(float dt)
{
	if(m_pCurrentExample != NULL)
	{
		m_pCurrentExample->Update(dt);
	}

	if(!m_uiVisible && !m_world.Initialising())
	{
		m_view.Show();
		m_uiVisible = true;
	}
}

void ExampleController::Draw()
{
	if(m_pCurrentExample != NULL)
	{
		m_pCurrentExample->Draw();
	}
}

void ExampleController::RegisterExample(IExampleFactory* pFactory)
{
	Eegeo_ASSERT(pFactory != NULL);
	m_factories.push_back(pFactory);
}

void ExampleController::DestroyCurrentExample()
{
	if(m_pCurrentExample != NULL)
	{
		m_pCurrentExample->Suspend();
		Eegeo_DELETE m_pCurrentExample;
		m_pCurrentExample = NULL;
	}
}

bool ExampleController::Event_TouchRotate(const AppInterface::RotateData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchRotate(data);
	}

	return false;
}

bool ExampleController::Event_TouchRotate_Start(const AppInterface::RotateData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchRotate_Start(data);
	}

	return false;
}

bool ExampleController::Event_TouchRotate_End(const AppInterface::RotateData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchRotate_End(data);
	}

	return false;
}


bool ExampleController::Event_TouchPinch(const AppInterface::PinchData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchPinch(data);
	}

	return false;
}

bool ExampleController::Event_TouchPinch_Start(const AppInterface::PinchData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchPinch_Start(data);
	}

	return false;
}

bool ExampleController::Event_TouchPinch_End(const AppInterface::PinchData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchPinch_End(data);
	}

	return false;
}

bool ExampleController::Event_TouchPan(const AppInterface::PanData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchPan(data);
	}

	return false;
}

bool ExampleController::Event_TouchPan_Start(const AppInterface::PanData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchPan_Start(data);
	}

	return false;
}

bool ExampleController::Event_TouchPan_End(const AppInterface::PanData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchPan_End(data);
	}

	return false;
}

bool ExampleController::Event_TouchTap(const AppInterface::TapData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchTap(data);
	}

	return false;
}

bool ExampleController::Event_TouchDoubleTap(const AppInterface::TapData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchDoubleTap(data);
	}

	return false;
}

bool ExampleController::Event_TouchDown(const AppInterface::TouchData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchDown(data);
	}

	return false;
}

bool ExampleController::Event_TouchMove(const AppInterface::TouchData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchMove(data);
	}

	return false;
}

bool ExampleController::Event_TouchUp(const AppInterface::TouchData& data)
{
	if(m_pCurrentExample != NULL)
	{
		return m_pCurrentExample->Event_TouchUp(data);
	}

	return false;
}
