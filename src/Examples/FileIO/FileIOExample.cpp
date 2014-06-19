// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "FileIOExample.h"
#include <sstream>
#include <vector>

using namespace Eegeo::Helpers;

namespace Examples
{
FileIOExample::FileIOExample(IFileIO& fileIO,
                             Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_fileIO(fileIO)
	,m_globeCameraStateRestorer(cameraController)
{
}

void FileIOExample::Start()
{
	srand(time(0));
	Byte data[] = { 1, 2, 3, 4, 5 };

	std::stringstream ss;
	ss << "mydata_" << rand() << ".bytes";
	std::string filename = ss.str();

	bool exists = m_fileIO.Exists(filename);

	Eegeo_TTY("%s %s\n", filename.c_str(), exists ? "exists" : "does not exist");
	if(!m_fileIO.WriteFile(data, 5ul, filename))
	{
		Eegeo_TTY("Failed to write to filesystem!\n");
		return;
	}

	exists = m_fileIO.Exists(filename);
	Eegeo_TTY("%s now %s\n", filename.c_str(), exists ? "exists" : "does not exist");

	std::fstream stream;
	size_t size;
	if(m_fileIO.OpenFile(stream, size, filename))
	{
		Eegeo_TTY("Opened File!\n");

		std::vector<Byte> readBackData;
		readBackData.resize(size);
		stream.read((char*)&readBackData[0], size);

		for(int i = 0; i < size; ++ i)
		{
			Eegeo_TTY("Read %d at position %d\n", readBackData[i], i);
		}
	}

	stream.close();

	Eegeo_TTY("Trying to delete %s...\n", filename.c_str());
	bool deleted = m_fileIO.DeleteFile(filename);
	Eegeo_TTY("Deleting %s %s!\n", filename.c_str(), deleted ? "succeeded" : "failed");

	Eegeo_TTY("Done!\n");
}
}
