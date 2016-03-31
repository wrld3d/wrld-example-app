// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "WindowsApplicationConfigurationVersionProvider.h"

#include <vector>


namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            namespace
            {
                bool TryGetFixedFileInfo(VS_FIXEDFILEINFO& fixedFileInfo)
                {
                    ZeroMemory(&fixedFileInfo, sizeof(VS_FIXEDFILEINFO));

                    TCHAR filename[MAX_PATH + 1] = "";
                    if (GetModuleFileName(NULL, filename, MAX_PATH) == 0)
                    {
                        return false;
                    }

                    DWORD dummy;
                    DWORD size = GetFileVersionInfoSize(filename, &dummy);
                    if (size == 0)
                    {
                        return false;
                    }

                    std::vector<BYTE> buffer(size);
                    if (!GetFileVersionInfo(filename, NULL, size, buffer.data()))
                    {
                        return false;
                    }

                    UINT versionLen = 0;
                    VS_FIXEDFILEINFO* pFixedFileInfo = 0;
                    if (VerQueryValue(buffer.data(), TEXT("\\"), (void**)&pFixedFileInfo, (UINT *)&versionLen) == 0)
                    {
                        return false;
                    }

                    fixedFileInfo = *pFixedFileInfo;

                    return true;
                }
            }

            WindowsApplicationConfigurationVersionProvider::WindowsApplicationConfigurationVersionProvider()
            {
                VS_FIXEDFILEINFO fixedFileInfo;
                bool success = TryGetFixedFileInfo(fixedFileInfo);
                Eegeo_ASSERT(success, "failed to get app version information");

                std::stringstream version;
                version << HIWORD(fixedFileInfo.dwFileVersionMS) << "." << LOWORD(fixedFileInfo.dwFileVersionMS) << "."
                    << HIWORD(fixedFileInfo.dwFileVersionLS) << "." << LOWORD(fixedFileInfo.dwFileVersionLS);
                m_productVersion = version.str();

                std::stringstream buildNumber;
                buildNumber << HIWORD(fixedFileInfo.dwFileVersionLS);

                m_buildNumber = buildNumber.str();
            }

            std::string WindowsApplicationConfigurationVersionProvider::GetProductVersionString() const
            {
                return m_productVersion;
            }

            std::string WindowsApplicationConfigurationVersionProvider::GetBuildNumberString() const
            {
                return m_buildNumber;
            }
        }
    }
}