//
//  NavigationGraphExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 02/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "NavigationGraphExample.h"
#include "NavigationGraphRoad.h"
#include "CameraHelpers.h"
#include "DebugRenderable.h"

using namespace Eegeo::Rendering;
using namespace Eegeo::DebugRendering;
using namespace Eegeo::Resources::Roads::Navigation;

namespace
{
DebugRenderable* CreateVisualisation(RenderContext& renderContext,
                                     const Eegeo::v3& roadColor,
                                     const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph);
}

namespace Examples
{
NavigationGraphExample::NavigationGraphExample(RenderContext& renderContext,
        NavigationGraphRepository& navigationGraphRepository,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_navigationGraphRepository(navigationGraphRepository)
	,m_renderContext(renderContext)
	,m_addedHandler(*this)
	,m_removedHandler(*this)
	,m_globeCameraStateRestorer(cameraController)
{
}

void NavigationGraphExample::Start()
{
	srand(time(0)); //for colors
	m_navigationGraphRepository.RegisterAddedCallback(&m_addedHandler);
	m_navigationGraphRepository.RegisterRemovalCallback(&m_removedHandler);
}

void NavigationGraphExample::Suspend()
{
	m_navigationGraphRepository.UnregisterAddedCallback(&m_addedHandler);
	m_navigationGraphRepository.UnregisterRemovalCallback(&m_removedHandler);
}

void NavigationGraphExample::Draw()
{
	for(MapType::const_iterator it = m_navGraphsToVisualisers.begin(); it != m_navGraphsToVisualisers.end(); ++ it)
	{
		const NavigationGraph &navGraph = *it->first;
		DebugRenderable &renderable = *it->second;

		Eegeo::dv3 ecefPosition = navGraph.GetCellInfo().GetFaceCentreECEF() + Eegeo::dv3::FromSingle(navGraph.GetUpECEF() * 2.0f);
		Eegeo::v3 m_cameraRelativePosition = Eegeo::Camera::CameraHelpers::CameraRelativePoint(ecefPosition, m_renderContext.GetCameraOriginEcef());
		renderable.Draw(m_cameraRelativePosition);
	}
}

void NavigationGraphExample::HandleAddedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
{
	Eegeo::v3 roadColor((rand()%256)/256.0f, (rand()%256)/256.0f, (rand()%256)/256.0f);
	m_navGraphsToVisualisers[&navGraph] = CreateVisualisation(m_renderContext, roadColor, navGraph);
}

void NavigationGraphExample::HandleRemovedGraph(const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
{
	delete m_navGraphsToVisualisers[&navGraph];
	m_navGraphsToVisualisers.erase(m_navGraphsToVisualisers.find(&navGraph));
}
}

namespace
{
DebugRenderable* CreateVisualisation(RenderContext& renderContext,
                                     const Eegeo::v3& roadColor,
                                     const Eegeo::Resources::Roads::Navigation::NavigationGraph& navGraph)
{
	DebugRenderable* renderable = new DebugRenderable(renderContext, NULL);

	const NavigationGraph::TRoadsVector& roads = navGraph.GetRoads();

	const Eegeo::v3& roadColorStart = roadColor;
	const Eegeo::v3& roadColorEnd = roadColor;

	std::vector<Eegeo::v3> verts;
	std::vector<Eegeo::v3> colors;
	std::vector<Eegeo::v2> uvs;
	std::vector<u16> indices;

	const Eegeo::v3& up = navGraph.GetUpECEF();

	for (NavigationGraph::TRoadsVector::const_iterator iter = roads.begin(); iter != roads.end(); ++iter)
	{
		const NavigationGraphRoad& road = **iter;

		const std::vector<Eegeo::v3>& roadVerts = road.GetVertices();
		const float halfWidth = road.GetHalfWidth();

		const float paramScale = 1.f / (roadVerts.size() - 1);

		for (int i = 1; i < roadVerts.size(); ++i)
		{
			Eegeo::v3 v0 = roadVerts[i-1];
			Eegeo::v3 v1 = roadVerts[i];
			Eegeo::v3 segmentColorStart = Eegeo::v3::Lerp(roadColorStart, roadColorEnd, (i-1)*paramScale);
			Eegeo::v3 segmentColorEnd = Eegeo::v3::Lerp(roadColorStart, roadColorEnd, i*paramScale);

			const int indexBase = verts.size();
			Eegeo::v3 dir = (v1 - v0).Norm();
			Eegeo::v3 right = Eegeo::v3::Cross(up, dir).Norm();

			verts.push_back(v0 + right*halfWidth);
			verts.push_back(v0 - right*halfWidth);
			verts.push_back(v1 + right*halfWidth);
			verts.push_back(v1 - right*halfWidth);

			colors.push_back(segmentColorStart);
			colors.push_back(segmentColorStart);
			colors.push_back(segmentColorEnd);
			colors.push_back(segmentColorEnd);

			uvs.push_back(Eegeo::v2(0.f, 0.f));
			uvs.push_back(Eegeo::v2(0.f, 1.f));
			uvs.push_back(Eegeo::v2(1.f, 0.f));
			uvs.push_back(Eegeo::v2(1.f, 0.f));
			uvs.push_back(Eegeo::v2(0.f, 1.f));
			uvs.push_back(Eegeo::v2(1.f, 1.f));

			indices.push_back(indexBase + 0);
			indices.push_back(indexBase + 1);
			indices.push_back(indexBase + 2);
			indices.push_back(indexBase + 2);
			indices.push_back(indexBase + 1);
			indices.push_back(indexBase + 3);
		}
	}

	renderable->Build(verts, colors, indices, uvs);
	return renderable;
}
}
