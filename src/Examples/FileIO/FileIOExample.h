// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__FileIOExample__
#define __ExampleApp__FileIOExample__

#include "IExample.h"

#include "IFileIO.h"

namespace Examples
{
class FileIOExample : public IExample
{
private:
	Eegeo::Helpers::IFileIO& m_fileIO;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

public:
	FileIOExample(Eegeo::Helpers::IFileIO& m_fileIO,
	              Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

	static std::string GetName()
	{
		return "FileIOExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt) {}
	void Draw() {}
	void Suspend() {}
};
}


#endif /* defined(__ExampleApp__FileIOExample__) */
