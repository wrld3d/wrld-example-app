/*
 * PinsWithAttachedJavaUIExampleFactory.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: kimbleoperations
 */

#include "PinsWithAttachedJavaUIExampleFactory.h"
#include "PinsWithAttachedJavaUIExample.h"

using namespace Examples;

PinsWithAttachedJavaUIExampleFactory::PinsWithAttachedJavaUIExampleFactory(
		Eegeo::EegeoWorld& world,
		AndroidNativeState& nativeState)
: m_world(world)
, m_nativeState(nativeState)
{

}

IExample* PinsWithAttachedJavaUIExampleFactory::CreateExample() const
{
    return new Examples::PinsWithAttachedJavaUIExample(
    		m_world,
			m_nativeState,
			m_world.GetRenderContext(),
			m_world.GetTextureLoader(),
			m_world.GetGlBufferPool(),
			m_world.GetShaderIdGenerator(),
			m_world.GetMaterialIdGenerator(),
			m_world.GetVertexBindingPool(),
			m_world.GetVertexLayoutPool(),
			m_world.GetRenderableFilters(),
			m_world.GetCameraProvider(),
			m_world.GetTerrainHeightProvider(),
			m_world.GetEnvironmentFlatteningService());
}
